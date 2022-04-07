#pragma once
#include <vector>

#include "Types.h"

namespace Render
{
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

		explicit Material(Color3XM color);
		Material(const BYTE* pSysMem, Surface resolution,bool alpha = true);
		Material(Surface resolution, std::vector<Color3XM> colors);
		Material(Material& other);
		Material(Material&& other) noexcept;
		Material& operator=(Material&& other) noexcept;
		Material() = delete;
		~Material();

		void swap_channels(RGBChannel first, RGBChannel second) const;
		void reflect() const;
	};
}
