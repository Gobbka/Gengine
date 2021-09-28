#include "Material.h"
#include "Types.h"

Render::Material::Material(BYTE* pSysMem, Surface resolution,bool alpha)
	: _resolution(resolution)
{
	const auto res_int = resolution.to_vector2int();
	_pSysMem = new BYTE[res_int.x * res_int.y * 4];
	memcpy(_pSysMem, pSysMem, res_int.x * res_int.y * 4);
}

Render::Material::Material(Material& other)
	:
	_resolution(other._resolution)
{
	auto resolution = _resolution.to_vector2int();
	_pSysMem = new BYTE[resolution.x * resolution.y * 4];
	memcpy(_pSysMem, other._pSysMem, resolution.x * resolution.y * 4);
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

Render::Material::Material()
	: _pSysMem(nullptr),
	_resolution(0,0)
{
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

void Render::Material::reflect() const
{
	auto WIDTH = (int)_resolution.width;
	auto HEIGHT = (int)_resolution.height;

	auto* buffer = new BYTE[WIDTH * 4];
	
	for (int col = 0; col < HEIGHT / 2; col++)
	{
		memcpy(buffer, _pSysMem + col * WIDTH * 4, WIDTH * 4);
		memcpy(_pSysMem + col * WIDTH * 4,_pSysMem + WIDTH * (HEIGHT - 1 - col) * 4,WIDTH * 4);
		memcpy(_pSysMem + WIDTH * (HEIGHT - 1 - col) * 4, buffer, WIDTH * 4);
	}

	delete[] buffer;
}

void Render::Material::load_bitmap(BYTE* pSysMem, Surface resolution)
{
	auto width = (UINT)resolution.width;
	auto height = (UINT)resolution.height;
	_pSysMem = new BYTE[width * height * 4];
	memcpy(_pSysMem, pSysMem, width * height * 4);
	_resolution = resolution;
}
