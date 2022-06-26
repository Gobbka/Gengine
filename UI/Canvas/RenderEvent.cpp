#include "RenderEvent.h"

#include <Graphics.h>
#include <Render/Common/IGContext.h>

void Render::DrawEvent2D::set_alpha(float alpha) const
{

}

Render::DrawEvent2D::DrawEvent2D(GEGraphics* ctx, Canvas::DrawData* de)
	: CanvasDrawEvent(de)
	, _context(ctx)
{}

Render::CanvasDrawEvent::CanvasDrawEvent(Canvas::DrawData* data)
	: _draw_data(data)
{}

Render::EventDrawCmd Render::CanvasDrawEvent::newDrawCmd(UINT vertices,UINT indices, GETexture*texture) const
{
	texture = texture ? texture : _draw_data->default_texture;

	auto vertices_index = _draw_data->vertices.require(vertices);
	auto indices_index = _draw_data->indices.require(indices);

	auto stencil_layer = (unsigned char)(_stencil_layer >= 0 ? _stencil_layer : 0);
		
	_draw_data->draw_list.push(Canvas::DrawCmd{ 
		texture,
		indices_index,
		indices,
		vertices,
		vertices_index,stencil_layer,
		_stencil_mode
	});
	
	return { _draw_data->vertices.at(vertices_index) , _draw_data->indices.at(indices_index) };
}

void Render::CanvasDrawEvent::drawRect(Position2 pos, Surface resolution, Color3XM color) const
{
	static UINT rect_indices[]{0,1,2,1,3,2};

	auto draw_cmd = newDrawCmd(4,6);
	auto* vertices = draw_cmd.vertices;
	auto* indices = draw_cmd.indices;

	vertices[0] = UI::Vertex2D(pos,color,{0,0});
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 0,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y-resolution.height }, color, { 0,0 });
	vertices[3] = UI::Vertex2D({ pos.x+resolution.width,pos.y-resolution.height }, color, { 0,0 });

	memcpy(indices, rect_indices, sizeof(rect_indices));
}

void Render::CanvasDrawEvent::drawRect(Position2 pos, Surface resolution, GETexture* texture) const
{
	static UINT rect_indices[]{ 0,1,2,1,3,2 };

	auto draw_cmd = newDrawCmd(4, 6, texture);
	auto* vertices = draw_cmd.vertices;
	auto* indices = draw_cmd.indices;
	const auto color = Color3XM{ 1,1,1 };

	vertices[0] = UI::Vertex2D(pos, color, { 0,0 });
	vertices[1] = UI::Vertex2D({ pos.x + resolution.width,pos.y }, color, { 1,0 });
	vertices[2] = UI::Vertex2D({ pos.x,pos.y - resolution.height }, color, { 0,1 });
	vertices[3] = UI::Vertex2D({ pos.x + resolution.width,pos.y - resolution.height }, color, { 1,1 });

	memcpy(indices, rect_indices, sizeof(rect_indices));
}

Render::StencilUsage Render::CanvasDrawEvent::stencil(StencilUsage mode)
{
	_stencil_layer++;
	_stencil_mode = mode;
	return _stencil_mode;
}

void Render::CanvasDrawEvent::stencilEnd(StencilUsage mode)
{
	_stencil_layer--;
	_stencil_mode = mode;
}
