#pragma once
#include <iostream>

#define LogA(text) std::cout << text << '\n'
#define LogW(text) std::wcout << text << L'\n'

#define DebugAssert(exp) assert(exp)

struct GEAssert {
    bool succeeded;
#ifdef UNICODE
    void log(LPCWSTR message) const
    {
        if(!succeeded)
			LogW(message);
	}
#else
    void log(LPCSTR message)
    {
        if (!succeeded)
            LogA(message);
    }
#endif

#ifdef UNICODE
    void abort(LPCWSTR message) const
    {
        if (!succeeded)
        {
#ifdef WIN32
            MessageBoxW(nullptr, message, TEXT("Assertation failed"), MB_ICONERROR);
            exit(-1);
#endif
        }
    }
#else
    void abort(LPCSTR message)
    {
        if (!succeeded)
        {
#ifdef WIN32
            MessageBoxA(nullptr, message, "Assertation failed", MB_OK);
            exit(-1);
#endif
        }
    }
#endif

    GEAssert(bool status)
	    : succeeded(status)
    {}

    GEAssert(HRESULT hr)
	    : succeeded(SUCCEEDED(hr))
    {}
};

#define AllocLoggerConsole() AllocConsole(); \
freopen("CONIN$", "r", stdin); \
freopen("CONOUT$", "w", stdout); \
freopen("CONOUT$", "w", stderr) \

inline std::ostream& blue(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE
        | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& red(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& green(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& yellow(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream& white(std::ostream& s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
        FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

struct color {
    color(WORD attribute) :m_color(attribute) {};
    WORD m_color;
};

template <class _Elem, class _Traits>
std::basic_ostream<_Elem, _Traits>&
operator<<(std::basic_ostream<_Elem, _Traits>& i, color& c)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, c.m_color);
    return i;
}

