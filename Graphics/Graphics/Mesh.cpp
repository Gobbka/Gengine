#include "Mesh.h"

Render::Mesh::Mesh(IVertexBuffer* buffer, IIndexBuffer* index_buffer)
{
	this->buffer = buffer;
	this->index_buffer = index_buffer;
	this->topology = PrimitiveTopology::NONE;
}
