#include "assets_packer.h"
#include <Windows.h>
#include <fstream>

void AssetsPacker::add_file(const wchar_t* file)
{
	_files.push_back(file);
}

V1AssetsFileStruct* AssetsPacker::pack(short compression_method)
{
	DWORD payload_size = 0x0;
	DWORD header_size = 0x0;

	for(auto* file_path : _files)
	{
		std::ifstream input;
		input.open(file_path, std::ios::binary | std::ios::ate);

		payload_size += input.tellg();
		header_size += wcslen(file_path) + sizeof(DWORD) /*+data length*/ + sizeof(DWORD) /*+offset*/;
		
		input.close();
	}

	auto* packed = (V1AssetsFileStruct*)malloc(header_size + payload_size);
	if (packed == nullptr)
		return nullptr;

	packed->magic_word = 0x4247;
	packed->header_version = 0x1;
	packed->struct_size = sizeof(V1AssetsFileStruct) + payload_size + header_size;
	packed->compression_method = compression_method;
	packed->misc_flags = 0x0;
	packed->files_count = _files.size();
	packed->payload_offset = sizeof(V1AssetsFileStruct) + header_size;
	packed->payload_size = payload_size;
	
	return nullptr;
}
