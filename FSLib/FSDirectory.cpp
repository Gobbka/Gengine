#include "FSDirectory.h"
#include <Windows.h>
#include <fileapi.h>
#include <fstream>
FS::FSDirectory::FSDirectory(wchar_t* dir_path)
{
	_dir_path = dir_path;
}

void FS::FSDirectory::foreach(std::function<void(FSFile*)> callback)
{
	WIN32_FIND_DATA data;
	HANDLE handle;
	 
	handle = FindFirstFile(_dir_path, &data);
	if(handle != INVALID_HANDLE_VALUE)
	{
		FSFile file(data.cFileName, data.nFileSizeLow, nullptr);
		callback(&file);
	}

	while(FindNextFile(handle,&data))
	{
		FSFile file(data.cFileName, data.nFileSizeLow, nullptr);
		callback(&file);
	}
}
