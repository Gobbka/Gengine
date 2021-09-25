#include "IVertexBuffer.h"
#include "IIndexBuffer.h"

#include <cassert>
#include "../../Render/d3d/Vertex.h"

void Render::IVertexBuffer::count_normals(IIndexBuffer* buffer)
{
	auto index_size = buffer->get_size();
	
	// we count only triangles
	assert(index_size % 3 == 0);
	
	for(size_t i = 0;i < index_size;i+=3)
	{
		
	}
}

Render::Vertex& Render::IVertexBuffer::at(unsigned index) const
{
	return data[index];
}
