#include "FSObject.h"
#include <Windows.h>

bool FS::FSObject::is_directory() const
{
	auto attributes = GetFileAttributesW(path());
	if (attributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return attributes & FILE_ATTRIBUTE_DIRECTORY;
}

FS::FSObject::FSObject(std::wstring & path)
	: _path(path)
{
	
}

FS::FSObject::FSObject(std::wstring && path)
	: _path(path)
{

}
