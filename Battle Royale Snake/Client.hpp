#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <WinSock2.h>
#include <winsock.h>
#include <ws2tcpip.h>
#include <cstdint>

class Client {
public:
	Client();
	~Client();
	bool getRank(uint64_t& rank, size_t& particpantCount);
	bool updateScore(const uint64_t score);
	bool kill();
	operator bool() {
		return m_socketHandle != INVALID_SOCKET;
	}
private:
	enum Command : uint8_t {
		Invalid,
		SendScore,
		GetRank,
		Kill
	};
	struct send_packet {
		uint64_t m_score = 0u;
		Command m_command = Command::Invalid;
	};
	struct recv_packet {
		uint64_t m_rank = 0u;
		size_t m_particapantCount = 0u;
	};
	addrinfo* m_info = nullptr;
	SOCKET m_socketHandle = INVALID_SOCKET;
};

#endif