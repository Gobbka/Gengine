#include "Console.h"
#include <Windows.h>

auto* stdin_stream = stdin;
auto* stdout_stream = stdout;
auto* stderr_stream = stderr;

GEString GEConsole::readInput()
{
	auto* input = new wchar_t[999];
	const auto result = scanf_s("%998S", input, 998);
	input[998] = '\0';
	if(result != EOF)
	{
		return GEString(input);
	}
	throw std::exception("Cannot read console input");
}

long long GEConsole::readNumber()
{
	long long out;
	if(scanf_s("%d",&out))
	{
		return out;
	}
	return 0;
}

void GEConsole::show()
{
	AllocConsole();
	freopen_s(&stdin_stream,"CONIN$", "r", stdin);
	freopen_s(&stdout_stream,"CONOUT$", "w", stdout);
	freopen_s(&stderr_stream,"CONOUT$", "w", stderr);
}

void GEConsole::hide()
{
	FreeConsole();
}
