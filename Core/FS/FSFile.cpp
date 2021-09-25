#include "FSFile.h"


FS::FSFile::FSFile(std::wstring file_path, size_t file_size, char* data)
	: FSObject(file_path)
{
	_file_size = file_size;
}
