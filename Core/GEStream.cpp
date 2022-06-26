#include "GEStream.h"

#include <cstring>

GEStream::GEStream(char* data, size_t size)
	: _data(data)
	, _size(size)
{
}

GEStream::GEStream(size_t size)
	: _data(new char[size])
	, _size(size)
{
}

GEStream::~GEStream()
{
	delete[] _data;
}

size_t GEStream::size() const
{
	return _size;
}

char* GEStream::data() const
{
	return _data;
}

bool GEStream::copy(char* data, size_t size, size_t byte_offset) const
{
	if (size + byte_offset > _size)
		return false;

	memcpy(_data + byte_offset, data, size);

	return true;
}

