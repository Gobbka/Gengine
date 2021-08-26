#include "Parallelepiped.h"
#include "../../../Graphics.h"
#include "../../Events/RenderEvent.h"

UINT PARALLELEPIPED_INDEX_ARRAY[]{
	0,1,2,3,6,7,4,5,
	2,6,0,4,1,5,3,7
};

namespace Render {
	class IndexBuffer;

	Mesh Parallelepiped::make(Core::GraphicsContext* context,Position3 pos, Vector3 resolution)
	{
		auto* device = context->get_device();
		auto x = 0.f;
		auto y = 0.f;
		auto width = resolution.x;
		auto height = resolution.y;
		auto length = resolution.z;

		auto* vbuffer = device->alloc_vertex_buffer(8);
		auto* ptr = vbuffer->data;

		ptr[0].pos = { x,y,0 };
		ptr[1].pos = { x + width,y,0 };
		ptr[2].pos = { x,y - height,0 };
		ptr[3].pos = { x + width,y - height,0 };

		ptr[4].pos = { x,y,length };
		ptr[5].pos = { x + width,y,length };
		ptr[6].pos = { x,y - height,length };
		ptr[7].pos = { x + width,y - height,length };

		ptr[0].normal = { -1.f,1.f,-1.f };
		ptr[1].normal = { -1.f,1.f,1.f };
		ptr[2].normal = { -1.f,-1.f,-1.f };
		ptr[3].normal = { -1.f,-1.f,1.f };

		ptr[4].normal = { 1.f,1.f,-1.f };
		ptr[5].normal = { 1.f,1.f,1.f };
		ptr[6].normal = { 1.f,-1.f,-1.f };
		ptr[7].normal = { 1.f,-1.f,1.f };

		ptr[2].color = { 0,0,0 };
		ptr[3].color = { 1,0,0 };
		ptr[0].color = { 0,1,0 };
		ptr[1].color = { 1,1,0 };
		ptr[7].color = { 0,0,0 };
		ptr[6].color = { 1,0,0 };
		ptr[5].color = { 0,1,0 };
		ptr[4].color = { 1,1,0 };
		vbuffer->update();

		static auto* index_buffer = device->alloc_index_buffer(PARALLELEPIPED_INDEX_ARRAY, ARRAYSIZE(PARALLELEPIPED_INDEX_ARRAY));
		
		return Mesh(vbuffer, index_buffer);
	}
}
