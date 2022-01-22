#include "GEStream.h"

GEStream::GEStream(char* data, unsigned size)
	: _data(data)
	, _size(size)
{
}

unsigned GEStream::size() const
{
	return _size;
}

char& GEStream::operator[](unsigned index) const
{
	return _data[index];
}
