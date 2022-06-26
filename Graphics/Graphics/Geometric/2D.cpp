#include "2D.h"
#include "../../Render/Common/Graphics.h"
#include "../../Render/d3d/Vertex.h"
#include "../../Render/Common/VBuffer.h"

UINT RECTANGLE_INDEX_ARRAY[] = { 0,1,2,1,3,2 };

Render::Mesh Geometric_2D::make_rectangle(Render::GEGraphics* gfx, Position2 pos, Surface resolution)
{
	auto* device = gfx->get_device();
	auto x = pos.x;
	auto y = pos.y;
	
	auto width = resolution.width;
	auto height = resolution.height;

	auto* ptr = new Render::Vertex[4];

	ptr[0] = Render::Vertex({ x,y,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0,0 });
	ptr[1] = Render::Vertex({ x+width,y,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0,0 });
	ptr[2] = Render::Vertex({ x,y-height,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0,0 });
	ptr[3] = Render::Vertex({ x+width,y-height,0 }, { 0,0,0 }, { 0,0,0 }, { 0,0,0,0 });

	Render::VBufferDesc desc;
	desc.usage = Render::VBufferDesc::Usage::immutable;
	desc.length = 4;
	desc.stride_size = sizeof(Render::Vertex);
	desc.p_data = ptr;

	auto* vbuffer = new Render::GEVBuffer<Render::Vertex>(gfx,desc);// device->alloc_vertex_buffer(ptr, desc);
	auto* index_buffer = device->alloc_index_buffer(RECTANGLE_INDEX_ARRAY, ARRAYSIZE(RECTANGLE_INDEX_ARRAY));

	return Render::Mesh(vbuffer, index_buffer);
}
