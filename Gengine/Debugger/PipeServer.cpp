#include "PipeServer.h"

#include <iostream>
#include <string>
#include <Windows.h>

PipeServer::PipeServer(LPCWSTR address)
{
	_hCreateNamedPipe = CreateNamedPipe(
		address,
		PIPE_ACCESS_DUPLEX | PIPE_TYPE_BYTE | PIPE_READMODE_BYTE,
		PIPE_WAIT,
		PIPE_UNLIMITED_INSTANCES,
		999999,
		999999,
		NMPWAIT_USE_DEFAULT_WAIT,
		nullptr
	);

	if (_hCreateNamedPipe == INVALID_HANDLE_VALUE) {
		std::cout << "NamedPipe creation failed with error number: " << GetLastError() << '\n';
	}
}

PipeServer::~PipeServer()
{
	DisconnectNamedPipe(_hCreateNamedPipe);
	CloseHandle(_hCreateNamedPipe);
}

PipeServer* PipeServer::create(LPCWSTR address)
{
	return new PipeServer(address);
}

DWORD PipeServer::receive(char** buffer) const
{
	DWORD dwRead=0;
	std::string wholescript;
	char receive_buffer[256];
	
	if (ConnectNamedPipe(_hCreateNamedPipe, NULL) != FALSE)
	{
		while (ReadFile(_hCreateNamedPipe, receive_buffer, sizeof(receive_buffer) - 1, &dwRead, NULL) != FALSE)
		{
			receive_buffer[dwRead] = '\0';
			wholescript += receive_buffer;
		}

	}
	DisconnectNamedPipe(_hCreateNamedPipe);

	auto length = wholescript.size();
	*buffer = new char[length];
	wholescript.copy(*buffer, length+1);
	(*buffer)[length] = '\0';
	
	return length;
}
