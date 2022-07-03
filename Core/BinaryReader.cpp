#include "BinaryReader.h"

#include <fstream>
#include <winerror.h>
#include "FS/FSFile.h"

BinaryReader::BinaryReader(_In_z_ wchar_t const* fileName) noexcept(false)
	: _pos(nullptr)
	, _end(nullptr)
	, _data(nullptr)
{
	auto data_size = 0ull;
	const auto result = readEntireFile(fileName, &_data, &data_size);

	assert(result);

	_pos = _data;
	_end = _data + data_size;
}

BinaryReader::BinaryReader(_In_reads_bytes_(dataSize) uint8_t const* dataBlob, size_t dataSize) noexcept
	: _pos(dataBlob),
	_end(dataBlob + dataSize),
	_data(nullptr)
{
}

BinaryReader::BinaryReader(BinaryReader&& other) noexcept(true)
	: _pos(other._pos)
	, _end(other._end)
	, _data(other._data)
{
	other._data = nullptr;
	other._pos = nullptr;
	other._end = nullptr;
}

BinaryReader& BinaryReader::operator=(BinaryReader&& other) noexcept
{
	if (_data != other._data)
		delete[] _data;
	_data = other._data;
	_end = other._end;
	_pos = other._pos;

	other._data = nullptr;
	other._end = nullptr;
	other._pos = nullptr;

	return*this;
}

char* BinaryReader::toString() const
{
	auto* buffer = new char[available()+1];
	buffer[available()] = '\0';
	memcpy(buffer, _data, _end - _data);
	return buffer;
}

bool BinaryReader::readEntireFile(_In_z_ wchar_t const* fileName, _Inout_ uint8_t** data, size_t* dataSize)
{
	std::ifstream ifs(fileName,std::ios::binary | std::ios::ate);

	if (!ifs.is_open())
		return false;

	*dataSize = ifs.tellg();
	*data = new uint8_t[*dataSize];
	ifs.seekg(std::ios::beg);
	ifs.read((char*)*data, *dataSize);

	return true;
}

BinaryReader::~BinaryReader()
{
	delete[] _data;
}
