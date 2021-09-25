#pragma once
#include <string>
#include "FSObject.h"

namespace FS {
	class  __declspec(dllexport) FSFile : public FSObject
	{
		size_t _file_size;
	public:
		FSFile(std::wstring file_path,size_t file_size,char*data);
		~FSFile() = default;

		auto size() const { return _file_size; }
	};
}
