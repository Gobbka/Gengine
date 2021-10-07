#include "Material.h"
#include "Types.h"

Render::Material::Material(const BYTE* pSysMem, const Surface resolution,bool alpha)
	: _pSysMem(nullptr),
	_resolution(resolution)
{
	const auto res_int = resolution.to_vector2int();
	const auto square = res_int.x * res_int.y * 4;

	_pSysMem = new BYTE[square];
	memcpy(_pSysMem, pSysMem, square);
}

Render::Material::Material(Material& other)
	:
	_resolution(other._resolution)
{
	const auto resolution_int = _resolution.to_vector2int();
	const auto square = (resolution_int.x * resolution_int.y) * 4;
	_pSysMem = new BYTE[square];
	memcpy(_pSysMem, other._pSysMem, square);
}

Render::Material::Material(Material&& other) noexcept
	:
	_resolution(other._resolution)
{
	_pSysMem = other._pSysMem;

	other._pSysMem = nullptr;
	other._resolution = Surface(0, 0);
}

Render::Material::Material(Color3XM color)
	: _resolution(1,1)
{
	_pSysMem = new BYTE[4];
	_pSysMem[0] = (BYTE)(color.r * 255.f);
	_pSysMem[1] = (BYTE)(color.g * 255.f);
	_pSysMem[2] = (BYTE)(color.b * 255.f);
	_pSysMem[3] = 255;
	format = DXGI_FORMAT_R8G8B8A8_UNORM;
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
	const auto square = (int)(_resolution.width * _resolution.height);

	for(auto i = 0;i < square;i++)
	{
		auto* color = (BYTE*)&memory[i];
		const auto buffer = color[first];
		color[first] = color[second];
		color[second] = buffer;
	}
}

void Render::Material::reflect() const
{
	const auto width = (__int64)(int)_resolution.width;
	const auto height = (__int64)(int)_resolution.height;

	auto* buffer = new BYTE[width * 4];
	
	for (int col = 0; col < height / 2; col++)
	{
		memcpy(buffer, _pSysMem + col * width * 4, width * 4);
		memcpy(_pSysMem + col * width * 4,_pSysMem + width * (height - 1 - col) * 4,width * 4);
		memcpy(_pSysMem + width * (height - 1 - col) * 4, buffer, width * 4);
	}

	delete[] buffer;
}
