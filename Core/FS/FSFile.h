#pragma once
#include <string>
#include "FSObject.h"
#include "../GEStream.h"

namespace FS {
	class  __declspec(dllexport) File : public FSObject
	{
		size_t _file_size;
		char* _data;
	public:
		File(std::wstring file_path,size_t file_size,char*data);
		File(std::wstring file_path,size_t file_size,const char*data);
		explicit File(std::wstring file_path);
		~File();

		auto size() const { return _file_size; }
		bool remove() const;
		void write(char* data, size_t size);
		void write(const GEStream& data_stream);
	};
}
