#pragma once
#include <string>

#include "FSObject.h"

namespace FS {
	class  __declspec(dllexport) FSFile : public FSObject
	{
		size_t _file_size;
		char* _data;
	public:
		FSFile(wchar_t* file_path,size_t file_size,char*data);
		~FSFile();

		auto* data() { return _data; }
		auto size() { return _file_size; }
		
		static FSFile read_file(wchar_t* file_path);
	};
}
