#include "Parallelepiped.h"
#include "../../../Graphics.h"
#include "../../d3d/Vertex.h"

UINT PARALLELEPIPED_INDEX_ARRAY[]{
	0,1,2,1,3,2, // front
	1,5,3,5,7,3, // right
	5,4,7,4,6,7, // back
	4,0,6,0,2,6, // left
	4,5,0,5,1,0, // up
	2,3,6,3,7,6, // down
};

UINT PARALLELEPIPED_INDEPENDENT_INDEX_ARRAY[]{
	0,1,2,1,3,2,
	4,5,6,5,7,6,
	8,9,10,9,11,10,
	12,13,14,13,15,14,
	16,17,18,17,19,18,
	22,23,20,23,21,20,
};

namespace Render {
	class IndexBuffer;

	Mesh Parallelepiped::make(Core::GraphicsContext* context,Position3 pos, Vector3 resolution)
	{
		auto* device = context->get_device();
		auto x = pos.x;
		auto y = pos.y;
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

	Mesh Parallelepiped::make_independent(Core::GraphicsContext* context, Position3 pos, Vector3 resolution)
	{
		auto* device = context->get_device();
		auto x = pos.x;
		auto y = pos.y;
		auto z = pos.z;
		auto width = resolution.x;
		auto height = resolution.y;
		auto length = resolution.z;

		auto* vbuffer = device->alloc_vertex_buffer(24);
		auto* ptr = vbuffer->data;
		// front
		ptr[0] = Vertex({ x,y,z }, { 0,0,0 }, { 0,0,-1 });
		ptr[1] = Vertex({ x + width,y,z }, { 1,0,0 }, { 0,0,-1 });
		ptr[2] = Vertex({ x ,y - height,z }, { 0,1,0 }, { 0,0,-1 });
		ptr[3] = Vertex({ x + width ,y - height,z }, { 1,1,0 }, { 0,0,-1 });
		// right
		ptr[4] = Vertex({ x + width,y,z }, { 0,0,0 }, { 1,0,0 });
		ptr[5] = Vertex({ x + width,y,z+length},{1,0,0},{1,0,0});
		ptr[6] = Vertex({ x + width ,y - height,z }, { 0,1,0 }, { 1,0,0 });
		ptr[7] = Vertex({ x + width ,y - height,z + length }, { 1,1,0 }, { 1,0,0 });
		// back
		ptr[8]  = Vertex({ x + width,y,z + length }, { 0,0,0 }, { 0,0,1 });
		ptr[9]  = Vertex({ x,y,z + length }, { 1,0,0 }, { 0,0,1});
		ptr[10] = Vertex({ x + width,y-height,z + length }, { 0,1,0 }, { 0,0,1 });
		ptr[11] = Vertex({ x,y-height,z + length }, { 1,1,0 }, { 0,0,1 });
		//left
		ptr[12] = Vertex({ x,y,z + length }, { 0,0,0 }, { -1,0,0 });
		ptr[13] = Vertex({ x,y,z }, { 1,0,0 }, { -1,0,0 });
		ptr[14] = Vertex({ x,y-height,z+length }, { 0,1,0 }, { -1,0,0 });
		ptr[15] = Vertex({ x,y-height,z }, { 1,1,0 }, { -1,0,0 });
		// up
		ptr[16] = Vertex({ x,y,z + length }, { 0,0,0 }, { 0,1,0 });
		ptr[17] = Vertex({ x+width,y,z + length }, { 1,0,0 }, { 0,1,0 });
		ptr[18] = Vertex({ x,y,z }, { 0,1,0 }, { 0,1,0 });
		ptr[19] = Vertex({ x+width,y,z }, { 1,1,0 }, { 0,1,0 });
		// down
		ptr[20] = Vertex({ x,y - height,z + length }, { 0,0,0 }, { 0,-1,0 });
		ptr[21] = Vertex({ x + width,y - height,z + length }, { 1,0,0 }, { 0,-1,0 });
		ptr[22] = Vertex({ x,y - height,z }, { 0,1,0 }, { 0,-1,0 });
		ptr[23] = Vertex({ x + width,y - height,z }, { 1,1,0 }, { 0,-1,0 });
		
		vbuffer->update();

		static auto* index_buffer = device->alloc_index_buffer(PARALLELEPIPED_INDEPENDENT_INDEX_ARRAY, ARRAYSIZE(PARALLELEPIPED_INDEPENDENT_INDEX_ARRAY));

		return Mesh(vbuffer, index_buffer);
	}
}
