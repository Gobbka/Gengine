#include "Mesh.h"

Render::Mesh::Mesh(IVertexBuffer<Vertex>* buffer, GEIndexBuffer* index_buffer)
	: buffer(buffer)
	, index_buffer(index_buffer)
	, topology(PrimitiveTopology::NONE)
{
}
