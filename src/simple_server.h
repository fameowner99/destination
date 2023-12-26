#pragma once

#include <crow.h>
#include "data_storage.h"

class SimpleServer
{
public:
    SimpleServer(const DataStorage&);

    void Run();

private:
    crow::SimpleApp app;
    const DataStorage &data_storage;

    const uint16_t port = 40080;
    const std::string address = "127.0.0.1";
};