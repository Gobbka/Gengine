#pragma once
#include "../BinaryReader.h"

class GECache
{
public:
	static BinaryReader load(const wchar_t*name);
	static void write(BinaryReader& reader, unsigned seconds = 3600);
};
