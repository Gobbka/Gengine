#pragma once
#include "../BinaryReader.h"

class GECache
{
	typedef time_t timestamp;

public:

	static BinaryReader load(const wchar_t*name);
	template<typename T>
	static T* load(const wchar_t*name);
	static void write(const wchar_t*name,char*data,size_t size, unsigned seconds = 3600);
	static void write(const wchar_t*name,BinaryReader& data, unsigned seconds = 3600);
};

template <typename T>
T* GECache::load(const wchar_t* name)
{
	auto reader = load(name);
	if(sizeof(T) == reader.available())
	{
		return reader.Read<T>();
	}
	return nullptr;
}
