#include "CanvasImpl.h"

#include "Graphics.h"
#include "IGContext.h"
#include "RenderEvent.h"

Canvas::DrawData* Canvas::CanvasImpl::begin()
{
	_drawData.allocator.clear();
	_drawData.draw_list.clear();

	return &_drawData;
}

void Canvas::CanvasImpl::present() 
{
	if(_drawData.allocator.length() > _buffer->get_size())
	{
		delete _buffer;
		_buffer = _context->get_device()->alloc_vertex_buffer<UI::Vertex2D>(_drawData.allocator.length()+500, true);
	}
	memcpy(&_buffer->at(0), _drawData.allocator.at(0), _drawData.allocator.size());
	_buffer->update(_drawData.allocator.length());
	_buffer->bind();

	auto* context = _context->get_context();
	auto* batch = _context->get_sprite_engine();

	for(const auto draw_cmd : _drawData.draw_list)
	{
		batch->bind_texture(draw_cmd.texture, 0);
		context->draw(draw_cmd.vtx_count,draw_cmd.vtx_offset);
	}
}

Canvas::CanvasImpl::CanvasImpl(Core::GraphicsContext* context)
	: _buffer(context->get_device()->alloc_vertex_buffer<UI::Vertex2D>(100u,true))
	, _context(context)
{
	Render::Material white(Color3XM{ 1,1,1 });
	_drawData.default_texture = new Render::Texture(context, white);
}

Core::GraphicsContext* Canvas::CanvasImpl::gfx()
{
	return _context;
}
