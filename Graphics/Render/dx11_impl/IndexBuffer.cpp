#include "IndexBuffer.h"
#include "../../Graphics.h"

Render::DX11IndexBuffer::DX11IndexBuffer(Core::DX11Graphics* graphics_context, UINT* index, size_t size)
	: _context(graphics_context)
	, _size(size)
	, _data(index)
	, _index_buffer(nullptr)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * size;
	desc.StructureByteStride = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sb_data{ index,0,0 };
	
	_context->device->CreateBuffer(&desc, &sb_data, &_index_buffer);
}

void Render::DX11IndexBuffer::bind()
{
	_context->context->IASetIndexBuffer(_index_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void Render::DX11IndexBuffer::update()
{
	_context->context->UpdateSubresource(_index_buffer, 0, nullptr, _data, 0, 0);
}

Render::DX11IndexBuffer::~DX11IndexBuffer()
{
	if(_index_buffer)
		_index_buffer->Release();
}
