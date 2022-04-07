#include "Material.h"
#include "Types.h"

Render::Material::Material(const BYTE* pSysMem, const Surface resolution,bool alpha)
	: _pSysMem(nullptr)
	, _resolution(resolution)
{
	const auto square = resolution.square() * 4;

	_pSysMem = new BYTE[square];
	memcpy(_pSysMem, pSysMem, square);
}

Render::Material::Material(Surface resolution, std::vector<Color3XM> colors)
	: _pSysMem(new BYTE[resolution.square() * 4])
	, _resolution(resolution)
{
}

Render::Material::Material(Material& other)
	: _resolution(other._resolution)
{
	const auto square = _resolution.square() * 4;
	_pSysMem = new BYTE[square];
	memcpy(_pSysMem, other._pSysMem, square);
}

Render::Material::Material(Material&& other) noexcept
	: _pSysMem(other._pSysMem)
	, _resolution(other._resolution)
{
	other._pSysMem = nullptr;
	other._resolution = Surface(0, 0);
}

Render::Material& Render::Material::operator=(Material&& other) noexcept
{
	if (_pSysMem != other.pSysMem())
		delete[]_pSysMem;
	_pSysMem = other._pSysMem;
	_resolution = other._resolution;
	format = other.format;

	other._pSysMem = nullptr;
	other._resolution = { 0,0 };
	other.format = DXGI_FORMAT_UNKNOWN;

	return*this;
}

Render::Material::Material(Color3XM color)
	: _pSysMem(new BYTE[4])
	, _resolution(1,1)
	, format(DXGI_FORMAT_R8G8B8A8_UNORM)
{
	_pSysMem[0] = (BYTE)(color.r * 255.f);
	_pSysMem[1] = (BYTE)(color.g * 255.f);
	_pSysMem[2] = (BYTE)(color.b * 255.f);
	_pSysMem[3] = 255;
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
	const auto square = _resolution.square();

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
