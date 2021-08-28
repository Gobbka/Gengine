#pragma once
#include "Types/Types.h"

namespace Render
{
	struct Color4Byte
	{
		char r, g, b, a;
	};

	struct Color3Byte
	{
		char r, g, b;
	};
	
	class __declspec(dllexport) Material
	{
		BYTE* _pSysMem;
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
		
		Material(BYTE* pSysMem, Surface resolution,bool alpha = true);
		~Material();

		void swap_channels(RGBChannel first, RGBChannel second) const;
		void reflect();
	};
}
