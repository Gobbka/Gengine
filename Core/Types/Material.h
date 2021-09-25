#pragma once
#include "Types.h"

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
		DXGI_FORMAT format = DXGI_FORMAT_B8G8R8A8_UNORM;

		enum class RGBChannel
		{
			red = 0,
			green = 1,
			blue = 2,
			alpha = 3,
		};
		
		void* pSysMem() const { return _pSysMem; }

		auto width() const { return _resolution.width; }
		auto height() const { return _resolution.height; }
		
		Material(BYTE* pSysMem, Surface resolution,bool alpha = true);
		Material(Material& other);
		Material(Material&& other) noexcept;
		Material(Color3 color);
		Material();
		~Material();

		void swap_channels(RGBChannel first, RGBChannel second) const;
		void reflect();

		void load_bitmap(BYTE*pSysMem,Surface resolution);
	};
}
