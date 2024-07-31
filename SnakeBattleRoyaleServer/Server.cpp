#include "Server.hpp"
#include <ws2def.h>
#include <iostream>
#include <algorithm>

#define BIND_HOST "0.0.0.0"
#define SERVER_PORT "42069"


void clientCallback(std::mutex& mutex, std::unordered_map<SOCKET, uint64_t>& ranks, SOCKET clientSocket) {
    Command lastCommand = Command::Invalid;
    while (lastCommand != Command::Kill) {
        command_packet packet;
        if (SOCKET_ERROR == recv(clientSocket, reinterpret_cast<char*>(&packet), sizeof(packet), 0))
            continue;
        switch (packet.m_command) {
            case Command::Kill: {
                closesocket(clientSocket);
                std::lock_guard<std::mutex> lock(mutex);
                ranks.erase(clientSocket);
                break;
            }
            case Command::GetRank: {
                std::lock_guard<std::mutex> lock(mutex);
                rank_packet sendPacket;
                auto clientScore = ranks[clientSocket];
                std::vector<uint64_t> scores;
                for (auto& kv : ranks) {
                    auto score = kv.second;
                    scores.push_back(score);
                }
                std::sort(scores.begin(), scores.end());
                std::reverse(scores.begin(), scores.end()); // Lazy but not efficient will change
                size_t rank = 0;
                for (size_t index = 0; index < scores.size(); index++) {
                    if (scores[index] == clientScore) {
                        rank = index + 1;
                        break;
                    }
                }
                sendPacket.m_rank = static_cast<uint64_t>(rank);
                sendPacket.m_particapantCount = ranks.size();
                send(clientSocket, reinterpret_cast<char*>(&sendPacket), sizeof(sendPacket), 0);
                break;
            }
            case Command::SendScore: {
                std::lock_guard<std::mutex> lock(mutex);
                ranks[clientSocket] = packet.m_score;
                break;
            }
        }
    }
}

Server::Server() {
    WSADATA wsaData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        std::cout << "Failed to initalize winsocket api!" << std::endl;
    }
    if (0 == getaddrinfo(BIND_HOST,
        SERVER_PORT, nullptr, &m_info)) {
        m_socketHandle = socket(m_info->ai_family, m_info->ai_socktype,
            m_info->ai_protocol);
        if (SOCKET_ERROR == bind(m_socketHandle, m_info->ai_addr, m_info->ai_addrlen)) {
            std::cout << "Failed to bind 0.0.0.0:4269 check if the port is being used." << std::endl;
            closesocket(m_socketHandle);
            freeaddrinfo(m_info);
            m_info = nullptr;
            m_socketHandle = INVALID_SOCKET;
            return;
        }
        if (SOCKET_ERROR == listen(m_socketHandle, SOMAXCONN)) {
            std::cout << "Failed to listen for connections on 0.0.0.0:4269 check if the port is being used." << std::endl;
            closesocket(m_socketHandle);
            freeaddrinfo(m_info);
            m_info = nullptr;
            m_socketHandle = INVALID_SOCKET;
            return;
        }
        std::cout << "Listening on 0.0.0.0:4269 for connections" << std::endl;
    }
    else {
        std::cout << "Could not resolve host (Error Code: " << WSAGetLastError() << ")" << std::endl;
    }
}

Server::~Server() {
    for (auto& thread : m_Threads) {
        thread.join();
    }
    if (m_socketHandle != INVALID_SOCKET)
        closesocket(m_socketHandle);
    if (m_info)
        freeaddrinfo(m_info); 
    WSACleanup();
}

void Server::startAcceptingClients() {
    for (;;) { 
        auto clientSocket = accept(m_socketHandle, nullptr, nullptr);
        if (clientSocket == SOCKET_ERROR)
            continue;
        std::cout << "A player is joining to play snake amongst others... [ CLIENT SOCKET CREATED ]" << std::endl;
        std::thread clientThread(clientCallback, std::ref(m_mutex), std::ref(m_ranks), clientSocket);
        m_Threads.push_back(std::move(clientThread));
    }
}
