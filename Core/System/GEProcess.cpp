#include "GEProcess.h"

#ifdef _WIN32
#include <Windows.h>

GEProcess::GEProcess(long long id)
	: _id(id)
{
}

GEString GEProcess::getCurrentProcessFileName()
{
    const auto module = GetModuleHandleW(nullptr);
    wchar_t buffer[1024];
    GetModuleFileNameW(module, buffer, 1023);
    return GEString{ buffer };
}

GEProcess GEProcess::startProcess()
{
    STARTUPINFO info = {sizeof(STARTUPINFO)};

    return GEProcess(0);
}

#endif
