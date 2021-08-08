#pragma once
#include <Windows.h>
class PipeServer
{

private:
	PipeServer(LPCWSTR address);
	~PipeServer();

	HANDLE _hCreateNamedPipe;
	
public:
	
	static PipeServer* create(LPCWSTR address);
	DWORD receive(char**buffer) const;
};
