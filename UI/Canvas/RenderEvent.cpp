#include "RenderEvent.h"

#include <Graphics.h>
#include <Render/Common/IGContext.h>

void Render::DrawEvent2D::mask_draw_begin()
{
}

void Render::DrawEvent2D::mask_discard_begin(bool increase_layer)
{
}

void Render::DrawEvent2D::mask_discard_end(bool decrease_layer)
{

}

void Render::DrawEvent2D::mask_set_stencil(BYTE new_index)
{
	_stencil_layer = new_index;
}

BYTE Render::DrawEvent2D::mask_get_stencil_layer() const
{
	return _stencil_layer;
}

void Render::DrawEvent2D::set_alpha(float alpha) const
{
	auto* context = _context->get_context();
	if(context->control_buffer.data.opacity != alpha)
	{
		context->control_buffer.data.opacity = alpha;
		context->control_buffer.update();
	}
}

Render::DrawEvent2D::DrawEvent2D(Core::GraphicsContext* ctx, Canvas::DrawData* de)
	: CanvasDrawEvent(de)
	, _context(ctx)
{}

Render::CanvasDrawEvent::CanvasDrawEvent(Canvas::DrawData* data)
	: _draw_data(data)
{}

Render::EventDrawCmd Render::CanvasDrawEvent::new_draw_cmd(UINT vertices,UINT indices, GETexture*texture) const
{
	texture = texture ? texture : _draw_data->default_texture;

	auto vertices_index = _draw_data->vertices.require(vertices);
	auto indices_index = _draw_data->indices.require(indices);
	
	_draw_data->draw_list.push(Canvas::DrawCmd{ texture,indices_index,indices,vertices,vertices_index });
	
	return { _draw_data->vertices.at(vertices_index) , _draw_data->indices.at(indices_index) };
}

void Render::CanvasDrawEvent::draw_rect(Position2 pos, Surface resolution, Color3XM color) const
{
	static UINT rect_indices[]{0,1,2,1,3,2};

	auto draw_cmd = new_draw_cmd(4,6);
	auto* vertices = draw_cmd.vertices;
	auto* indices = draw_cmd.indices;

	vertices[0] = UI::Vertex2D(pos,color,{0,0});
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 0,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y-resolution.height }, color, { 0,0 });
	vertices[3] = UI::Vertex2D({ pos.x+resolution.width,pos.y-resolution.height }, color, { 0,0 });

	memcpy(indices, rect_indices, sizeof(rect_indices));
}

void Render::CanvasDrawEvent::draw_rect(Position2 pos, Surface resolution, GETexture* texture) const
{
	static UINT rect_indices[]{ 0,1,2,1,3,2 };

	auto draw_cmd = new_draw_cmd(4, 6, texture);
	auto* vertices = draw_cmd.vertices;
	auto* indices = draw_cmd.indices;
	const auto color = Color3XM{ 1,1,1 };

	vertices[0] = UI::Vertex2D(pos, color, { 0,0 });
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 1,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y - resolution.height }, color, { 0,1 });
	vertices[3] = UI::Vertex2D({ pos.x + resolution.width,pos.y - resolution.height }, color, { 1,1 });

	memcpy(indices, rect_indices, sizeof(rect_indices));
}
