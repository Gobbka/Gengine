#include "FSObject.h"
#include <Windows.h>

bool FS::FSObject::isDirectory()
{
	auto attributes = GetFileAttributesW(wpath());
	if (attributes == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return attributes & FILE_ATTRIBUTE_DIRECTORY;
}

FS::FSObject::FSObject(GEString& string)
	: _path(string)
{

}

FS::FSObject::FSObject(GEString&& string)
	: _path(std::move(string))
{

}

FS::FSObject::FSObject(FSObject&& move) noexcept
	: _path(std::move(move._path))
{
}
