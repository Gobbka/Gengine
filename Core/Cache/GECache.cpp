#include "GECache.h"
#include <ctime>
#include "../FS/FSFile.h"
#include "../GEStream.h"

BinaryReader GECache::load(const wchar_t* name)
{
	BinaryReader reader{ name };
	const auto end_time = reader.Read<timestamp>();
	const auto time_now = time(nullptr);

	if(end_time - time_now < 0)
	{
		return { nullptr,0 };
	}
	
	return reader;
}

void GECache::write(const wchar_t* name, char* data, size_t size, unsigned seconds)
{
	const auto write_size = size + sizeof(timestamp);
	GEStream data_stream(write_size);
	data_stream.write(time(nullptr), 0);
	data_stream.copy(data, size, sizeof(timestamp));
	FS::File file(name);
	file.write(data_stream);
}
