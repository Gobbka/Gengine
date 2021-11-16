﻿#include "VertexBuffer.h"

#include "../../../Graphics.h"
#include "../Vertex.h"

void Render::VertexBuffer::copy_to(void* buffer, UINT size)
{
	memcpy(buffer, this->data, size * sizeof(Vertex));
}

Render::VertexBuffer::VertexBuffer(Core::GraphicsContext* engine, Vertex* data, size_t length, ID3D11Buffer* buffer)
	: IVertexBuffer(engine,data,length)
	, _buffer(buffer)
{}

void Render::VertexBuffer::copy_to(IVertexBuffer* buffer)
{
	const auto copy_size = min(this->size, buffer->get_size());

	memcpy(buffer->data, this->data, copy_size * sizeof(Vertex));
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



