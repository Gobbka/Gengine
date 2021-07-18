#include "FSObject.h"
#include <Windows.h>
// TODO: fix it
bool FS::FSObject::is_directory()
{
	auto attributes = GetFileAttributesW(path());
	if (attributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return attributes & FILE_ATTRIBUTE_DIRECTORY;
}

FS::FSObject::FSObject(std::wstring path)
	: _path(path)
{
	
}
