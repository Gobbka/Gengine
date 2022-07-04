#include "GEThread.h"

#ifdef _WIN32
#include <Windows.h>

GEThread::GEThread(void* routine, void* params)
	: _id(0)
{
	CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)routine, params, 0, &_id);
}

GEThread::~GEThread()
{
	if(_id)
	{
		TerminateThread(OpenThread(DELETE, 0, _id), 0);
	}
}

#endif
