#include "DX11ConstantBuffer.h"
#include "Graphics.h"
#include "Logger/Logger.h"

Render::DX11ConstantBuffer::DX11ConstantBuffer(GEGraphics* gfx,UINT data_size, UINT slot, BYTE binds)
	: _gfx(gfx)
	, _d3d_buffer(nullptr)
	, _slot(slot)
	, _binds(binds)
	, _data(new char[data_size])
{
	D3D11_BUFFER_DESC desc{ data_size,D3D11_USAGE_DEFAULT,D3D11_BIND_CONSTANT_BUFFER,0,0,0 };
	D3D11_SUBRESOURCE_DATA sd{ _data,0,0 };

	GEAssert(_gfx->device->CreateBuffer(&desc, &sd, &_d3d_buffer))
		.abort(TEXT("ConstantBuffer.cpp: cannot create constant buffer"));
}

void Render::DX11ConstantBuffer::update() const
{
	_gfx->context->UpdateSubresource(_d3d_buffer, 0, nullptr, _data, 0, 0);
}

void Render::DX11ConstantBuffer::bind() const
{
	if (_binds & CBBindFlag_vs)
		_gfx->context->VSSetConstantBuffers(_slot, 1, &_d3d_buffer);

	if (_binds & CBBindFlag_ps)
		_gfx->context->PSSetConstantBuffers(_slot, 1, &_d3d_buffer);
}

void* Render::DX11ConstantBuffer::data() const
{
	return _data;
}
