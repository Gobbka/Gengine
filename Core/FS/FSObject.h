#pragma once
#include "../GEString.h"

namespace FS
{
	class __declspec(dllexport) FSObject
	{
	protected:
		GEString _path;
	public:
		bool isDirectory();

		explicit FSObject(GEString& string);
		explicit FSObject(GEString&& string);

		explicit FSObject(FSObject&& move) noexcept;
		
		auto* wpath() { return _path.data(); }
		auto& path() { return _path; }
	};
}