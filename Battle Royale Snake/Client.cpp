#include "Client.hpp"
#include <ws2def.h>
#include "Constants.hpp"

bool Client::getRank(uint64_t& rank, size_t& particpantCount) {
    send_packet sendPacket = {};
    sendPacket.m_command = Command::GetRank;
    if (SOCKET_ERROR == send(m_socketHandle, reinterpret_cast<char*>(&sendPacket), sizeof(sendPacket), 0)) {
        return false;
    }
    recv_packet recvPacket = {};
    if (SOCKET_ERROR == recv(m_socketHandle, reinterpret_cast<char*>(&recvPacket), sizeof(recv_packet), 0)) {
        return false;
    }
    rank = recvPacket.m_rank;
    particpantCount = recvPacket.m_particapantCount;
    return true;
}

bool Client::updateScore(const uint64_t score) {
    send_packet sendPacket = {};
    sendPacket.m_command = Command::SendScore;
    sendPacket.m_score = score;
    if (SOCKET_ERROR == send(m_socketHandle, reinterpret_cast<char*>(&sendPacket), sizeof(sendPacket), 0)) {
        return false;
    }
    return true;
}

bool Client::kill() // Tell server this client has game over'ed
{
    send_packet sendPacket = {};
    sendPacket.m_command = Command::Kill;
    if (SOCKET_ERROR == send(m_socketHandle, reinterpret_cast<char*>(&sendPacket), sizeof(sendPacket), 0)) {
        return false;
    }
    return true; // Destructor will handle the closing of socket handle
}


Client::Client() {
    WSADATA wsaData;
    if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData)) {
        return;
    }
    if (0 == getaddrinfo(SERVER_ADDRESS,
        SERVER_PORT, nullptr, &m_info)) {
        m_socketHandle = socket(m_info->ai_family, m_info->ai_socktype,
            m_info->ai_protocol);
        if (SOCKET_ERROR == connect(m_socketHandle, m_info->ai_addr, m_info->ai_addrlen)) {
            closesocket(m_socketHandle);
            freeaddrinfo(m_info);
            m_info = nullptr;
            m_socketHandle = INVALID_SOCKET;
        }
    }
}

Client::~Client() {
    if (m_info)
        freeaddrinfo(m_info);
    if (m_socketHandle != INVALID_SOCKET)
        closesocket(m_socketHandle);
    WSACleanup();
}