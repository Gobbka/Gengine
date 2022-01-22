#pragma once

class GEStream
{
	char* _data;
	unsigned _size;
public:
	GEStream(char* data, unsigned size);
	unsigned size() const;
	char& operator[](unsigned index) const;
};
