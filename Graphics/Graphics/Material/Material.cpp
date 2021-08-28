#include "Material.h"
#include <fstream>

#include "../../../Libs/FreeImage/FreeImage.h"
#include "Types/Types.h"

Render::Material::Material(BYTE* pSysMem, Surface resolution,bool alpha)
	: _resolution(resolution)
{
	_pSysMem = (BYTE*)malloc(resolution.width * resolution.height * 4);// pSysMem;
	if(alpha || true)
		memcpy(_pSysMem, pSysMem, resolution.width * resolution.height * 4);
	else
	{
		for(int i = 0;i < resolution.width * resolution.height;i++)
		{
			auto dst = (Color4Byte*)_pSysMem;
			auto src = (Color3Byte*)pSysMem;

			auto pixel = src[i];
			
			dst[i] = Color4Byte{ pixel.r,pixel.g,pixel.b,(char)0xff };
		}
	}
}

Render::Material::~Material()
{
	delete[] _pSysMem;
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

void Render::Material::reflect()
{
	auto WIDTH = _resolution.width;
	auto HEIGHT = _resolution.height;
	
	for (int row = 0; row < WIDTH / 2; row++)
	{
		for (int col = 0; col < HEIGHT; col++)
		{
			//*(int*)((char*)(_pSysMem[row]) + col) = 0xFFFFFFFF;

		}
	}
}
