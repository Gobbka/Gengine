#pragma once

struct AssetsFileHeader
{
	short magic_word;
	short header_version;
	size_t struct_size;
};

struct V1AssetFileHeader
{
	unsigned long data_size;
	unsigned long data_offset;
	char name[1];
};

struct V1AssetsFileStruct : AssetsFileHeader
{
	short compression_method;
	short misc_flags;
	size_t files_count;
	unsigned long payload_offset;
	unsigned long payload_size;
	/* all files in format: size(8 byte) offset(8 byte) file_name\0 */
	/* data */
};
