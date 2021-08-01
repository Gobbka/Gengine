#include "IndexBuffer.h"
#include "../../../Graphics.h"

Render::IndexBuffer::IndexBuffer(Core::GraphicsContext* graphics_context, UINT* index, size_t size)
	: IIndexBuffer(graphics_context)
{
	_index = index;
	_size = size;
	
	D3D11_BUFFER_DESC desc;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DYNAMIC;
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

Render::IndexBuffer::~IndexBuffer()
{
}
