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

	std::wstring file_path = wpath();
	file_path = file_path + L"\\*";
	
	handle = FindFirstFile(file_path.c_str(), &data);
	if(handle != INVALID_HANDLE_VALUE)
	{
		if(wcscmp(data.cFileName,L".") != 0)
		{
			std::wstring filename(path());
			filename = filename + L'\\' + data.cFileName;

			File file(filename, data.nFileSizeLow, (char*)nullptr);
			callback(&file);
		}
	}

	while(FindNextFile(handle,&data))
	{	
		std::wstring filename(path());
		filename = filename + L'\\' + data.cFileName;
		
		File file(filename, data.nFileSizeLow, (char*)nullptr);
		callback(&file);
	}
}
