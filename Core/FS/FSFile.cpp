#include "FSFile.h"
#include <fstream>

FS::File::File(std::wstring file_path, size_t file_size, char* data)
	: FSObject(file_path)
	, _file_size(file_size)
	, _data(data)
{
}

FS::File::File(std::wstring file_path, size_t file_size, const char* data)
	: FSObject(file_path)
	, _file_size(file_size)
	, _data(new char[file_size])
{
	memcpy(_data, data, _file_size);
}

FS::File::File(std::wstring file_path)
	: FSObject(file_path)
	, _file_size(0)
	, _data(nullptr)
{
}

FS::File::~File()
{
	delete[] _data;
}

bool FS::File::remove() const
{
	return _wremove(path());
}

void FS::File::write(char* data, size_t size)
{
	_data = data;
	_file_size = size;
	std::ofstream ofs(path(),std::ios::binary | std::ios::out);
	
}

void FS::File::write(const GEStream& data_stream)
{
	return write(data_stream.data(), data_stream.size());
}
