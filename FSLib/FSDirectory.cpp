#include "FSDirectory.h"
#include <Windows.h>
#include <fileapi.h>
#include <fstream>
FS::FSDirectory::FSDirectory(wchar_t* dir_path)
	: FSObject(std::wstring(dir_path))
{
}

void FS::FSDirectory::foreach(std::function<void(FSObject*)> callback)
{
	WIN32_FIND_DATA data;
	HANDLE handle;
	 
	handle = FindFirstFile(path(), &data);
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
