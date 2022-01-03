#include "Mesh.h"

Render::Mesh::Mesh(IVertexBuffer<Vertex>* buffer, IIndexBuffer* index_buffer)
	: buffer(buffer)
	, index_buffer(index_buffer)
	, topology(PrimitiveTopology::NONE)
{
}
