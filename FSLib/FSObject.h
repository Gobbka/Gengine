#pragma once
#include <string>

namespace FS
{
	class __declspec(dllexport) FSObject
	{
	protected:
		std::wstring _path;
	public:
		bool is_directory();
		
		FSObject(std::wstring path);
		
		auto* path() { return _path.c_str(); }
	};
}