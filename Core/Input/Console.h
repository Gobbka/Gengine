#pragma once
#include "../GEString.h"

class __declspec(dllexport) GEConsole
{
public:
	static GEString readInput();
	static long long readNumber();

	static void show();
	static void hide();
};
