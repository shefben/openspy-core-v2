#include <OS/Config/AppConfig.h>
#include <OS/Task/TaskScheduler.h>

#include "tasks.h"


namespace MM {
	const char *mm_channel_exchange = "openspy.master";
    const char *mp_pk_name = "QRID";

	TaskScheduler<UTMasterRequest, TaskThreadData>::RequestHandlerEntry requestTable[] = {
		{UTMasterRequestType_AllocateServerId, PerformAllocateServerId},
		{UTMasterRequestType_Heartbeat, PerformHeartbeat},
		{UTMasterRequestType_ListServers, PerformListServers},
		{NULL, NULL}
	};

    TaskScheduler<UTMasterRequest, TaskThreadData> *InitTasks(INetServer *server) {
        TaskScheduler<UTMasterRequest, TaskThreadData> *scheduler = new TaskScheduler<UTMasterRequest, TaskThreadData>(OS::g_numAsync, server, requestTable, NULL);

        scheduler->SetThreadDataFactory(TaskScheduler<UTMasterRequest, TaskThreadData>::DefaultThreadDataFactory);

		scheduler->DeclareReady();

        return scheduler;
    }

}