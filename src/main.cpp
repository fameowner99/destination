#include "data_storage.h"
#include "simple_server.h"

int main() {
    DataStorage data_storage("destinations.csv");
    data_storage.Parse();

    SimpleServer server(data_storage);
    server.Run();

    return 0;
}
