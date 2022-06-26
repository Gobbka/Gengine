#include "Mesh.h"

Render::Mesh::Mesh(GEVBuffer_Impl* buffer, GEIndexBuffer* index_buffer)
	: buffer(buffer)
	, index_buffer(index_buffer)
	, topology(PrimitiveTopology::NONE)
{
}
