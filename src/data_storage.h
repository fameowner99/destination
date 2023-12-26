#pragma once

#include <filesystem>

struct Coordinates
{
    double latitude;
    double longitude;
};

class DataStorage
{
public:
    explicit DataStorage(const std::filesystem::path &path);
    void Parse();

    const std::unordered_map<std::string, Coordinates> &Get() const
    {
        return data_map;
    }

private:
    std::filesystem::path storage_path;
    std::unordered_map<std::string, Coordinates> data_map;
};