#pragma once

class GEThread
{
	unsigned long _id;
public:
	explicit GEThread(void* routine, void* params = nullptr);
	~GEThread();
};
