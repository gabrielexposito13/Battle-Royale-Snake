#ifndef SERVER_HPP
#define SERVER_HPP

#include <WinSock2.h>
#include <winsock.h>
#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <ws2tcpip.h>

enum Command : uint8_t {
	Invalid,
	SendScore,
	GetRank,
	Kill
};
struct command_packet {
	uint64_t m_score = 0u;
	Command m_command = Command::Invalid;
};
struct rank_packet {
	uint64_t m_rank = 0u;
	size_t m_particapantCount = 0u;
};

class Server {
public:
	Server();
	~Server();
	operator bool() {
		return INVALID_SOCKET != m_socketHandle;
	}
	void startAcceptingClients();
private:
	addrinfo* m_info = nullptr;
	SOCKET m_socketHandle = INVALID_SOCKET;
	std::vector<std::thread> m_Threads;
	std::unordered_map<SOCKET, uint64_t> m_ranks; // Ordered hash map mapping a socket client handle to there current rank.
	std::mutex m_mutex;
};

#endif