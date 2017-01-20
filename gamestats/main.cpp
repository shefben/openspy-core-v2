#include <stdio.h>
#include <map>
#include <string>
#include <sstream>
#include <OS/Net/NetServer.h>
#include <OS/socketlib/socketlib.h>
#include "server/GPServer.h"
#include "server/GPDriver.h"
INetServer *g_gameserver = NULL;

int main() {
    OS::Init();
    Socket::Init();

	g_gameserver = new GP::Server();
	g_gameserver->addNetworkDriver(new GP::Driver(g_gameserver, "0.0.0.0", STATS_SERVER_PORT));
	g_gameserver->init();
	while(true) {
		g_gameserver->tick();
	}
}


#ifdef _WIN32

int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;

    GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}


#endif

