#include "Material.h"

#include "../../../ResourceManager/Drivers/ImageDriver.h"

Render::Material::Material(void* pSysMem, Surface resolution)
	: _resolution(resolution)
{
	_pSysMem = pSysMem;
}

void Render::Material::swap_channels(RGBChannel _first, RGBChannel _second) const
{
	auto* memory = (Color4Byte*)_pSysMem;
	
	const auto first = (UINT)_first;
	const auto second = (UINT)_second;
	
	for(auto i = 0;i < _resolution.width * _resolution.height;i++)
	{
		auto* color = (BYTE*)&memory[i];
		const auto buffer = color[first];
		color[first] = color[second];
		color[second] = buffer;
	}
}
