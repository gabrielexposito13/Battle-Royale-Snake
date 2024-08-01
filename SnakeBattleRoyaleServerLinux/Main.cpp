#include "Server.hpp"
#include <iostream>

int main()
{
    std::cout << "Starting Battle Royale Snake Server..." << std::endl;
    Server server;
    if (!server) {
        return 0;
    }
    server.startAcceptingClients();
    return 0;
}
