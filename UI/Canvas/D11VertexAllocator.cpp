#include "D11VertexAllocator.h"

#include <Graphics.h>

Render::IVertexBuffer<UI::Vertex2D>* Render::D11VertexAllocator::alloc_vbuffer(UINT size) const
{	
	return _ctx->get_device()->alloc_vertex_buffer<UI::Vertex2D>(size, true);
}

void Render::D11VertexAllocator::set_vbuffer(IVertexBuffer<UI::Vertex2D>* buffer)
{
	delete _vertex_buffer;
	_vertex_buffer = buffer;
}

UINT Render::D11VertexAllocator::buffer_size() const
{
	return _vertex_buffer->get_size();
}

UINT Render::D11VertexAllocator::last_index() const
{
	return _allocator.allocated;
}

Core::GraphicsContext* Render::D11VertexAllocator::get_graphics_context() const
{
	return _ctx;
}

void Render::D11VertexAllocator::update() const
{
	// replace with allocates_size
	if (buffer_size() <= 0)
		return;

	_vertex_buffer->update(last_index());
}

void Render::D11VertexAllocator::alloc(UINT size)
{
	if (last_index() + size > buffer_size())
	{
		const int needed = (last_index() + size) / _allocator.step_size + 1;

		auto* new_buffer = this->alloc_vbuffer(needed * _allocator.step_size);
		_vertex_buffer->copy_to(new_buffer);
		this->set_vbuffer(new_buffer);
	}

	_allocator.allocated += size;
}

UI::Vertex2D* Render::D11VertexAllocator::get_ptr() const
{
	return _vertex_buffer->data;
}

void Render::D11VertexAllocator::bind() const
{
	_vertex_buffer->bind();
}

Render::D11VertexAllocator::D11VertexAllocator(Core::GraphicsContext* pEngine, IVertexBuffer<UI::Vertex2D>* buffer)
	: _ctx(pEngine)
	, _allocator(100,100)
	, _vertex_buffer(buffer)
{
	_allocator.allocated = (UINT)buffer->get_size();
}

Render::D11VertexAllocator::D11VertexAllocator(Core::GraphicsContext* pEngine)
	: _ctx(pEngine)
	, _allocator(100, 100)
	, _vertex_buffer(nullptr)
{
	this->set_vbuffer(this->alloc_vbuffer(_allocator.start_size));
}

Render::D11VertexAllocator::~D11VertexAllocator()
{
	// delete _vertex_buffer;
}
