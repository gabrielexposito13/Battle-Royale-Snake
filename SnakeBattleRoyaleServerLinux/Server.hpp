#ifndef SERVER_HPP
#define SERVER_HPP


#include <cstdint>
#include <vector>
#include <thread>
#include <mutex>
#include <unordered_map>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h> 

#define SOCKET_ERROR -1
#define INVALID_SOCKET -1

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
	int m_socketHandle = INVALID_SOCKET;
	std::vector<std::thread> m_Threads;
	std::unordered_map<int, uint64_t> m_ranks; // Ordered hash map mapping a socket client handle to there current rank.
	std::mutex m_mutex;
};

#endif