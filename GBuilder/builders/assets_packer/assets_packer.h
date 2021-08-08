#pragma once
#include <vector>
#include "assets_file_struct.h"

class AssetsPacker
{
	std::vector<const wchar_t*> _files;
public:
	enum class CompressionMethod : unsigned char
	{
		compress_repetition = 0b1,
		haffman_coding = 0b10
	};
	
	void add_file(const wchar_t* file);

	V1AssetsFileStruct* pack(short compression_method = 0x0);
};
