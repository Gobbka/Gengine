#include "D3D11Canvas.h"
#include "../Render/Engine/D3DEngine.h"
#include "../Render/d3d/Buffer/VertexBuffer.h"

Render::VertexBuffer* Render::D3D11Canvas::alloc_vbuffer(UINT size) const
{
	auto* buffer = new Vertex[size];
	return new VertexBuffer(_engine,buffer,size,true);
}

void Render::D3D11Canvas::set_vbuffer(VertexBuffer* buffer)
{
	delete _vertex_buffer;
	_vertex_buffer = buffer;
}

UINT Render::D3D11Canvas::buffer_size() const
{
	return _vertex_buffer->size;
}

UINT Render::D3D11Canvas::get_allocated_size() const
{
	return _allocator.allocated;
}

Render::D3DEngine* Render::D3D11Canvas::get_engine() const
{
	return _engine;
}

void Render::D3D11Canvas::update() const
{
	if (buffer_size() <= 0)
		return;

	_vertex_buffer->update(get_allocated_size());
}

void Render::D3D11Canvas::alloc_vertexes(UINT size)
{
	if (get_allocated_size() + size > buffer_size())
	{
		const int needed = (get_allocated_size() + size) / _allocator.step_size + 1;

		auto* new_buffer = this->alloc_vbuffer(needed * _allocator.step_size);
		_vertex_buffer->copy_to(new_buffer);
		this->set_vbuffer(new_buffer);
	}

	_allocator.allocated += size;
}

Render::Vertex* Render::D3D11Canvas::get_ptr() const
{
	return _vertex_buffer->data;
}

Render::VertexBuffer* Render::D3D11Canvas::get_vbuffer() const
{
	return _vertex_buffer;
}

Render::D3D11Canvas::D3D11Canvas(D3DEngine* pEngine, VertexBuffer* buffer)
	:_allocator(100,100)
{
	_engine = pEngine;
	_vertex_buffer = buffer;
	_allocator.allocated = buffer->size;
}

Render::D3D11Canvas::D3D11Canvas(D3DEngine* pEngine)
	:_allocator(100, 100)
{
	_vertex_buffer = nullptr;
	_engine = pEngine;

	this->set_vbuffer(this->alloc_vbuffer(_allocator.start_size));
}

Render::D3D11Canvas::~D3D11Canvas()
{
	delete _vertex_buffer;
}
