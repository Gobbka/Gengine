#include "GECache.h"
#include "../FS/FSFile.h"
#include "time.h"

BinaryReader GECache::load(const wchar_t* name)
{
	BinaryReader reader{ name };
	const auto end_time = reader.Read<unsigned>();
	const auto time_now = time(nullptr);

	if(end_time - time_now < 0)
	{
		return { nullptr,0 };
	}

	return reader;
}

void GECache::write(BinaryReader& reader, unsigned seconds)
{
	
}
