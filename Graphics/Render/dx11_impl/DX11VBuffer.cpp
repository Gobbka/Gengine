#include "DX11VBuffer.h"

#include <exception>

#include "Graphics.h"

D3D11_USAGE get_d11_usage(Render::VBufferDesc::Usage usage)
{
	switch (usage)
	{
	case Render::VBufferDesc::Usage::classic:
		return D3D11_USAGE_DEFAULT;
	case Render::VBufferDesc::Usage::immutable:
		return D3D11_USAGE_IMMUTABLE;
	case Render::VBufferDesc::Usage::dynamic:
		return D3D11_USAGE_DYNAMIC;
	}
	throw std::exception("Unknown usage");
}

D3D11_BUFFER_DESC get_buffer_desc(Render::VBufferDesc v_desc)
{
	D3D11_BUFFER_DESC dx11_desc;
	dx11_desc.Usage = get_d11_usage(v_desc.usage);
	dx11_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	dx11_desc.CPUAccessFlags = v_desc.usage == Render::VBufferDesc::Usage::dynamic ? D3D11_CPU_ACCESS_WRITE : 0u;
	dx11_desc.MiscFlags = 0;
	dx11_desc.StructureByteStride = v_desc.stride_size;
	dx11_desc.ByteWidth = v_desc.stride_size * v_desc.length;
	return dx11_desc;
}

Render::DX11VBuffer::DX11VBuffer(GEGraphics* graphics, VBufferDesc v_desc)
	: desc(v_desc)
	, _graphics(graphics)
	, _buffer(nullptr)
{
	const auto dx11_desc = get_buffer_desc(v_desc);

	desc.p_data = v_desc.p_data ? v_desc.p_data : new char[dx11_desc.ByteWidth];

	D3D11_SUBRESOURCE_DATA sd{ desc.p_data,0,0 };

	assert(SUCCEEDED(_graphics->device->CreateBuffer(&dx11_desc, &sd, &_buffer)));
}

Render::DX11VBuffer::DX11VBuffer(DX11VBuffer& copy)
	: _graphics(copy._graphics)
	, _buffer(nullptr)
	, desc(copy.desc)
{
	const auto dx11_desc = get_buffer_desc(desc);

	desc.p_data = new char[dx11_desc.ByteWidth];

	D3D11_SUBRESOURCE_DATA sd{ desc.p_data,0,0 };

	assert(SUCCEEDED(_graphics->device->CreateBuffer(&dx11_desc, &sd, &_buffer)));
}

Render::DX11VBuffer::DX11VBuffer(DX11VBuffer&& move) noexcept
	: _graphics(move._graphics)
	, _buffer(move._buffer)
	, desc(move.desc)
{
	move.desc = {};
	move._buffer = nullptr;
	move._graphics = nullptr;
}

Render::DX11VBuffer::~DX11VBuffer()
{
	if(_buffer)
	{
		_buffer->Release();
	}
}

void Render::DX11VBuffer::bind() const
{
	const UINT offset = 0;
	const UINT stride = desc.stride_size;

	_graphics->context->IASetVertexBuffers(0, 1, &_buffer, &stride, &offset);
}

void Render::DX11VBuffer::update(UINT update_size) const
{
	update_size = min(update_size, desc.length);

	auto* pContext = _graphics->context;
	D3D11_MAPPED_SUBRESOURCE sub_data;

	pContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &sub_data);

	this->copyTo(sub_data.pData, update_size);

	pContext->Unmap(_buffer, 0);
}

void Render::DX11VBuffer::copyTo(DX11VBuffer* buffer) const
{
	if(buffer->desc.stride_size != desc.stride_size)
	{
		throw std::exception("Stride size are not the same");
	}

	const auto copy_length = min(desc.length, buffer->desc.length);
	memcpy(buffer->desc.p_data, desc.p_data, copy_length * desc.stride_size);
}

void Render::DX11VBuffer::copyTo(void* buffer, UINT size) const
{
	const auto copy_length = min(desc.length, size);
	memcpy(buffer, desc.p_data, copy_length * desc.stride_size);
}

size_t Render::DX11VBuffer::getLength() const
{
	return desc.length;
}
