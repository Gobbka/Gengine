#include "Material.h"

#include "../../../ResourceManager/Drivers/ImageDriver.h"

Render::Material::Material(void* pSysMem, Surface resolution)
	: _resolution(resolution)
{
	_pSysMem = pSysMem;
}

void Render::Material::swap_channels(RGBChannel first, RGBChannel second)
{
	auto* memory = (Color4Byte*)_pSysMem;

	
	for(auto i = 0;i < _resolution.width * _resolution.height;i++)
	{
		auto* color = (BYTE*)&memory[i];
		auto buffer = color[first];
		color[first] = color[second];
		color[second] = buffer;
	}
}
