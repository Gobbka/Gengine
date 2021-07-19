#include "VertexBuffer.h"
#include "../../Engine/Camera.h"
#include "../Vertex.h"

void Render::VertexBuffer::copy_to(VertexBuffer* buffer) const
{
	const auto copy_size = min(this->size, buffer->size);

	memcpy(buffer->data, this->data, copy_size * sizeof(Vertex));
}

void Render::VertexBuffer::copy_to(void* buffer, UINT size) const
{
	memcpy(buffer, this->data, size * sizeof(Vertex));
}

Render::VertexBuffer* Render::VertexBuffer::alloc(Core::GraphicsContext* engine, UINT size, bool dynamic)
{
	return new VertexBuffer(engine, new Vertex[size], size, dynamic);
}

Render::VertexBuffer::VertexBuffer(Core::GraphicsContext* engine, Vertex* data, UINT size, bool dynamic)
	: Bindable(engine)
{
	this->data = data;
	this->size = size;

	D3D11_BUFFER_DESC vbuffer{
		sizeof(Vertex) * size,
		dynamic ? D3D11_USAGE_DYNAMIC : D3D11_USAGE_DEFAULT,
		D3D11_BIND_VERTEX_BUFFER,
		(dynamic ? D3D11_CPU_ACCESS_WRITE : 0u),
		0,
		sizeof(Vertex)
	};
	D3D11_SUBRESOURCE_DATA sd{ data,0,0 };

	assert(SUCCEEDED(_engine->create_buffer(&vbuffer, &sd, &_buffer)));
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
	
	_engine->context()->IASetVertexBuffers(0, 1, &_buffer, &stride, &offset);
}

void Render::VertexBuffer::update(UINT update_size)
{
	update_size = min(update_size, this->size);

	auto* pContext = _engine->context();
	D3D11_MAPPED_SUBRESOURCE subdata;

	assert(SUCCEEDED( pContext->Map(_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subdata)));

	this->copy_to(subdata.pData, update_size);

	pContext->Unmap(_buffer, 0);
}



