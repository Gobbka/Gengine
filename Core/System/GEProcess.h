#pragma once
#include "../GEString.h"

class GEProcess
{
	long long _id;

	explicit GEProcess(long long id);
public:
	static GEString getCurrentProcessFileName();
	static GEProcess startProcess();
};
