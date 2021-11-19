#include "CanvasImpl.h"

#include "Graphics.h"
#include "IGContext.h"
#include "Objects/IObject.h"
#include "RenderEvent.h"

UI::Vertex2D* Canvas::CanvasImpl::vertices() const
{
	return _canvas.get_ptr();
}

Canvas::DrawData* Canvas::CanvasImpl::begin()
{
	const auto context = _canvas.get_graphics_context();
	const auto gcontext = context->get_context();

	_backupData = { gcontext->get_pixel_shader(),gcontext->get_vertex_shader() };

	gcontext->set_pixel_shader(context->shader_collection.get<Render::PixelShader>(L"d3d11\\canvas_ps.cso"));
	gcontext->set_vertex_shader(context->shader_collection.get_vs(L"d3d11\\canvas_vs.cso"));

	_drawData.allocator.clear();

	return &_drawData;
}

void Canvas::CanvasImpl::present() const
{
	auto* context = _canvas.get_graphics_context()->get_context();
	auto* batch = _canvas.get_graphics_context()->get_sprite_engine();

	for(const auto draw_cmd : _drawData.draw_list)
	{
		if (draw_cmd.texture)
			batch->bind_texture(draw_cmd.texture, 0);

		context->draw(draw_cmd.vtx_count,draw_cmd.vtx_offset);
	}
}

Canvas::CanvasImpl::CanvasImpl(Core::GraphicsContext* engine)
	: _canvas(engine)
{}

void Canvas::CanvasImpl::update() const
{
	_canvas.update();
}

void Canvas::CanvasImpl::render(Render::DrawEvent2D* event)
{
	bind();
	for (auto* object : _objects)
		if (!object->hidden)
			event->draw_object(object);
}

void Canvas::CanvasImpl::add_object(IObject* object)
{
	object->set_index(_canvas.last_index());
	_canvas.alloc(object->size());

	_objects.push_back(object);
	object->initialize(this);
}

void Canvas::CanvasImpl::bind() const
{
	_canvas.bind();
}

