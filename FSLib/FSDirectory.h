#pragma once
#include <functional>

#include "FSFile.h"

namespace FS {
	class FSDirectory
	{
		wchar_t* _dir_path;
	public:
		FSDirectory(wchar_t* dir_path);

		void foreach(std::function<void(FSFile*)> callback);
	};
}
