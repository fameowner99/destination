#include "simple_server.h"

namespace
{
#define PI 3.14159265358979323846
#define RADIO_TERRESTRE 6372797.56085
#define GRADOS_RADIANES PI / 180

// result in km
double CalculateDistance(const Coordinates &coord1, const Coordinates &coord2) {
    double lat_new = coord1.latitude * GRADOS_RADIANES;
    double lat_old = coord2.latitude * GRADOS_RADIANES;
    double lat_diff = (coord1.latitude - coord2.latitude) * GRADOS_RADIANES;
    double lng_diff = (coord1.longitude - coord2.longitude) * GRADOS_RADIANES;

    double a = sin(lat_diff / 2) * sin(lat_diff / 2) +
               cos(lat_new) * cos(lat_old) *
                       sin(lng_diff / 2) * sin(lng_diff / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));

    double distance = RADIO_TERRESTRE * c;

    return distance / 1000;
}
}

SimpleServer::SimpleServer(const DataStorage& data)
: data_storage(data)
{
    CROW_ROUTE(app,"/destinations/<string>/<int>")
    ([this](const std::string &destination , int radius){

        if (!data_storage.Get().count(destination))
        {
            return crow::response(404, "No such destination");
        }

        const auto destination_data = data_storage.Get().at(destination);

        std::map<double, std::string> result;
        for (const auto &location : data_storage.Get())
        {
            if (location.first == destination)
            {
                continue;
            }

            const auto distance = CalculateDistance(destination_data, location.second);
            if (distance <= radius)
            {
                result[distance] = location.first;
            }
        }

        std::stringstream ss;

        ss << "{" << std::endl;
        for (const auto &r : result)
        {
            ss << "\"" << r.second << "\": " << r.first << std::endl;
        }
        ss << "}" << std::endl;

        return crow::response(ss.str());
    });
}

void SimpleServer::Run()
{
    app.bindaddr(address).port(port).run();
}