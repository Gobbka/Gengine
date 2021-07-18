#include "FSFile.h"

#include <cassert>
#include <fstream>

FS::FSFile::FSFile(wchar_t* file_path, size_t file_size, char* data)
	: FSObject(std::wstring(file_path))
{
	_file_size = file_size;
	_data = data;
}

FS::FSFile::~FSFile()
{
	delete[] _data;
}

FS::FSFile FS::FSFile::read_file(wchar_t* file_path)
{
	std::ifstream ifs(file_path, std::ios::in | std::ios::binary | std::ifstream::ate);

	assert(ifs.is_open());

	auto size = (size_t)ifs.tellg();

	ifs.seekg(0);

	auto* ptr = new char[size];
	ifs.read(ptr, size);

	return FSFile(file_path,size,ptr);
}
