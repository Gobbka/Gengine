#pragma once
#include <functional>

#include "FSFile.h"

namespace FS {
	class __declspec(dllexport) FSDirectory : public FSObject
	{
	public:
		FSDirectory(GEString path);

		void foreach(std::function<void(FSObject*)> callback);
	};
}
