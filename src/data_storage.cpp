#include "data_storage.h"

#include <fstream>
#include <sstream>
#include <iostream>

namespace
{
    void LTrimSpaces(std::string& s)
    {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) { return !std::isspace(ch); }));
    }

    // trim from end
    void RTrimSpaces(std::string& s)
    {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) { return !std::isspace(ch); }).base(), s.end());
    }

    // trim from both ends
    void TrimSpaces(std::string& s)
    {
        RTrimSpaces(s);
        LTrimSpaces(s);
    }

    std::vector<std::string> SplitString(const std::string& str, const char delimeter)
    {
        std::stringstream ss(str);
        std::vector<std::string> vstrings;
        std::string token;

        while (getline(ss, token, delimeter))
        {
            TrimSpaces(token);
            vstrings.push_back(token);
        }

        return vstrings;
    }
}

DataStorage::DataStorage(const std::filesystem::path &path)
: storage_path(path)
{

}

void DataStorage::Parse()
{
    std::ifstream infile(storage_path);

    std::string line;
    std::getline(infile, line); // skip first line
    while (std::getline(infile, line))
    {
       const auto splited_data = SplitString(line, ',');

       if (splited_data.size() != 4)
       {
            continue;
       }

       try
       {
            data_map[splited_data[1]] = Coordinates{stod(splited_data[2]), stod(splited_data[3])};
       }
       catch (std::exception &e)
       {

       }

    }
}