#include "FSDirectory.h"
#include <Windows.h>
#include <fileapi.h>
#include <fstream>

FS::FSDirectory::FSDirectory(GEString path)
	: FSObject(std::move(path))
{
}

void FS::FSDirectory::foreach(std::function<void(FSObject*)> callback)
{
	WIN32_FIND_DATA data;

	auto file_path = path() + GEString{L"\\*"};

	const auto handle = FindFirstFile(file_path.data(), &data);
	if(handle != INVALID_HANDLE_VALUE)
	{
		FindNextFile(handle, &data);
	}

	while(FindNextFile(handle,&data))
	{	
		GEString file_name = path() + GEString{ L"\\" } + GEString{ data.cFileName };
		
		File file(std::move(file_name), data.nFileSizeLow, (char*)nullptr);
		callback(&file);
	}
}
