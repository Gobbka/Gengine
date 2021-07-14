#pragma once
#include <map>

#include "ImageDriver.h"

class __declspec(dllexport) PNGImageDriver
{
	struct PNGChunk
	{
		unsigned size;
		char* data_ptr;
	};
	static void parse_chunks(DriverInput input, std::map<unsigned, PNGChunk>*map);
public:
	static DriverOutput to_data_byte4(DriverInput input);
};
