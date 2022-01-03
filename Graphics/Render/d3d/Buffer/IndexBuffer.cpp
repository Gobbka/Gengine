#include "IndexBuffer.h"
#include "../../../Graphics.h"

Render::IndexBuffer::IndexBuffer(Core::GraphicsContext* graphics_context, UINT* index, size_t size)
	: IIndexBuffer(graphics_context,size,index)
{
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = sizeof(UINT) * size;
	desc.StructureByteStride = 0;
	desc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA sb_data{ index,0,0 };
	
	graphics_context->device->CreateBuffer(&desc, &sb_data, &_index_buffer);
}

void Render::IndexBuffer::bind()
{
	_engine->context->IASetIndexBuffer(_index_buffer, DXGI_FORMAT_R32_UINT, 0);
}

void Render::IndexBuffer::update()
{
	_engine->context->UpdateSubresource(_index_buffer, 0, nullptr, data, 0, 0);
}

Render::IndexBuffer::~IndexBuffer()
{
	if(_index_buffer)
		_index_buffer->Release();
}
