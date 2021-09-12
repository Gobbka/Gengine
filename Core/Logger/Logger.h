#pragma once
#include <iostream>

#define LogA(text) std::cout << text << '\n'
#define LogW(text) std::wcout << text << L'\n'

#define AllocLoggerConsole() AllocConsole(); \
freopen("CONIN$", "r", stdin); \
freopen("CONOUT$", "w", stdout); \
freopen("CONOUT$", "w", stderr) \
