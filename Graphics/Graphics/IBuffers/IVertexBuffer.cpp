#include "IVertexBuffer.h"
#include "../../Render/d3d/Vertex.h"

Render::Vertex& Render::IVertexBuffer::at(unsigned index) const
{
	return data[index];
}
