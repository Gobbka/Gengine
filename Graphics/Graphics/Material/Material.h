#pragma once
#include "../Types.h"

namespace Render
{
	class __declspec(dllexport) Material
	{
		void* _pSysMem;
		Surface _resolution;
	public:
		enum class RGBChannel
		{
			red = 0,
			green = 1,
			blue = 2,
			alpha = 3,
		};
		
		void* pSysMem() { return _pSysMem; };

		auto width() { return _resolution.width; }
		auto height() { return _resolution.height; }
		
		Material(void* pSysMem, Surface resolution);

		void swap_channels(RGBChannel first, RGBChannel second) const;
	};
}
