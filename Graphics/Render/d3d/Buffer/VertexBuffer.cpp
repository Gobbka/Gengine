#include "VertexBuffer.h"

#include "../../../Graphics.h"
#include "../Vertex.h"

D3D11_USAGE get_d11_usage(Render::IVertexBufferDesc::Usage usage)
{
	switch (usage)
	{
	case Render::IVertexBufferDesc::Usage::classic:
		return D3D11_USAGE_DEFAULT;
		break;
	case Render::IVertexBufferDesc::Usage::immutable:
		return D3D11_USAGE_IMMUTABLE;
	case Render::IVertexBufferDesc::Usage::dynamic:
		return D3D11_USAGE_DYNAMIC;
	}
}

void Render::VertexBuffer::copy_to(void* buffer, UINT size)
{
	memcpy(buffer, this->data, size * sizeof(Vertex));
}

void Render::VertexBuffer::copy_to(IVertexBuffer* buffer)
{
	const auto copy_size = min(this->size, buffer->get_size());

	memcpy(buffer->data, this->data, copy_size * sizeof(Vertex));
}

Render::VertexBuffer::VertexBuffer(Core::GraphicsContext* engine, Vertex* data, IVertexBufferDesc desc)
	: IVertexBuffer(engine,desc.size)
{
	this->data = data;

	D3D11_BUFFER_DESC vbuffer{
		sizeof(Vertex) * size,
		get_d11_usage(desc.usage),
		D3D11_BIND_VERTEX_BUFFER,
		(desc.usage == IVertexBufferDesc::Usage::dynamic ? D3D11_CPU_ACCESS_WRITE : 0u),
		0,
		sizeof(Vertex)
	};
	D3D11_SUBRESOURCE_DATA sd{ data,0,0 };
	
	assert(SUCCEEDED(_engine->device->CreateBuffer(&vbuffer, &sd, &_buffer)));
}

Render::VertexBuffer::~VertexBuffer()
{
	if (_buffer)
		_buffer->Release();
	delete[] data;
}

void Render::VertexBuffer::bind()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	_engine->context->IASetVertexBuffers(0, 1, &_buffer, &stride, &offset);
}

void Render::VertexBuffer::update(UINT update_size)
{
	update_size = min(update_size, this->size);

	auto* pContext = _engine->context;
	D3D11_MAPPED_SUBRESOURCE subdata;

	pContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata);

	this->copy_to(subdata.pData, update_size);

	pContext->Unmap(_buffer, 0);
}



