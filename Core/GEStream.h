#pragma once

class GEStream
{
	char* _data;
	size_t _size;
public:
	GEStream(char* data, size_t size);
	explicit  GEStream(size_t size);
	~GEStream();

	size_t size() const;
	char* data() const;

	template<typename T>
	bool write(T& data, size_t byte_offset);
	template<typename T>
	bool write(T data, size_t byte_offset);
	bool copy(char* data, size_t size, size_t byte_offset) const;
};

template <typename T>
bool GEStream::write(T& data, size_t byte_offset)
{
	return copy(&data, sizeof(T), byte_offset);
}

template <typename T>
bool GEStream::write(T data, size_t byte_offset)
{
	return copy((char*) & data, sizeof(T), byte_offset);
}
