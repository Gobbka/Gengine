#pragma once
#include "../Types.h"

namespace Render
{
	class __declspec(dllexport) Material
	{
		void* _pSysMem;
		Surface _resolution;
	public:
		void* pSysMem() { return _pSysMem; };

		auto width() { return _resolution.width; }
		auto height() { return _resolution.height; }
		
		Material(void* pSysMem, Surface resolution);
	};
}
