#ifndef _GPDRIVER_H
#define _GPDRIVER_H
#include <stdint.h>
#include "../main.h"
#include <OS/Net/NetDriver.h>

#include "GPPeer.h"

#include <map>
#include <vector>
#ifdef _WIN32
#include <time.h>
#else
#include <sys/time.h>
#endif

#include <OS/GPShared.h>

#define GP_PING_TIME (120)

namespace GP {
	class Peer;
	class Driver;
	class Driver : public INetDriver {
	public:
		Driver(INetServer *server, const char *host, uint16_t port);
		~Driver();
		void think(bool packet_waiting);
		int getListenerSocket();
		uint16_t getPort();
		uint32_t getBindIP();
		uint32_t getDeltaTime();

		Peer *find_client(struct sockaddr_in *address);
		Peer *find_or_create(struct sockaddr_in *address);

		bool HasPeer(Peer *);
		Peer *FindPeerByProfileID(int profileid);

		void InformStatusUpdate(int from_profileid, GPShared::GPStatus status);

		int GetNumConnections();
		const std::vector<int> getSockets();
		const std::vector<INetPeer *> getPeers();
	private:

		void TickConnections();

		int m_sd;

		std::vector<Peer *> m_connections;
		
		struct sockaddr_in m_local_addr;

		struct timeval m_server_start;

		std::vector<GP::Peer *> m_peers_to_delete;

	};
}
#endif //_SBDRIVER_H