#pragma once
#include <string>

namespace FS
{
	class __declspec(dllexport) FSObject
	{
	protected:
		std::wstring _path;
	public:
		bool isDirectory() const;
		
		FSObject(std::wstring & path);
		FSObject(std::wstring && path);
		
		auto* path() const { return _path.c_str(); }
		auto wpath() { return _path; }
	};
}