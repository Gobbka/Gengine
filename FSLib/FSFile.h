#pragma once

namespace FS {
	class  __declspec(dllexport) FSFile
	{
		wchar_t* _file_path;
		size_t _file_size;
		char* _data;
	public:
		FSFile(wchar_t* file_path,size_t file_size,char*data);
		~FSFile();

		auto* data() { return _data; }
		auto size() { return _file_size; }
		auto* path() { return _file_path; }
		
		static FSFile read_file(wchar_t* file_path);
	};
}