#include "Cube.h"

#include "../../../Graphics.h"
#include "../../d3d/Buffer/IndexBuffer.h"
#include "../../d3d/Buffer/Texture.h"
#include "../../d3d/Buffer/VertexBuffer.h"

Render::IndexBuffer* CUBE_INDEX_BUFFER;

Render::Cube::Cube(Position3 pos,Core::GraphicsContext* context)
	: Parallelepiped(pos,context,Vector3(5,5,5))
{
}