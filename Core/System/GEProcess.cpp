#include "GEProcess.h"

#ifdef _WIN32
#include <Windows.h>

GEString GEProcess::getCurrentProcessFileName()
{
    const auto module = GetModuleHandleW(nullptr);
    wchar_t buffer[1024];
    GetModuleFileNameW(module, buffer, 1023);
    return GEString{ buffer };
}

#endif