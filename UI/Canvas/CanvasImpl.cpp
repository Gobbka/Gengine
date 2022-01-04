#include "CanvasImpl.h"

#include "Graphics.h"
#include <Render/Common/IGContext.h>
#include <Render/Common/IndexBuffer.h>

Canvas::DrawData* Canvas::CanvasImpl::begin()
{
	_drawData.vertices.clear();
	_drawData.indices.clear();
	_drawData.draw_list.clear();

	return &_drawData;
}

void Canvas::CanvasImpl::present() 
{
	if(_drawData.vertices.length() > _buffer->get_size())
	{
		delete _buffer;
		_buffer = _context->get_device()->alloc_vertex_buffer<UI::Vertex2D>(_drawData.vertices.length()+500, true);
	}
	if(_drawData.indices.length() > _ibuffer->get_size())
	{
		delete _ibuffer;
		_ibuffer = _context->get_device()->alloc_index_buffer(_drawData.vertices.length() + 500);
	}
	memcpy(&_buffer->at(0), _drawData.vertices.at(0), _drawData.vertices.size());
	memcpy(&_ibuffer->operator[](0), _drawData.indices.at(0), _drawData.indices.size());
	
	_ibuffer->update();
	_ibuffer->bind();
	_buffer->update(_drawData.vertices.length());
	_buffer->bind();

	auto* context = _context->get_context();
	auto* batch = _context->get_sprite_engine();

	for(const auto draw_cmd : _drawData.draw_list)
	{
		batch->bind_texture(draw_cmd.texture, 0);
		context->draw_indexed(draw_cmd.idx_count,draw_cmd.idx_offset,draw_cmd.vtx_offset);
	}
}

Canvas::CanvasImpl::CanvasImpl(Render::GEGraphics* context)
	: _buffer(context->get_device()->alloc_vertex_buffer<UI::Vertex2D>(100u,true))
	, _ibuffer(context->get_device()->alloc_index_buffer(100))
	, _context(context)
{
	Render::Material white(Color3XM{ 1,1,1 });
	_drawData.default_texture = new Render::GETexture(context, white);
}

Render::GEGraphics* Canvas::CanvasImpl::gfx() const
{
	return _context;
}
