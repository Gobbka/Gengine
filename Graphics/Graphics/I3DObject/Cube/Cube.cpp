#include "Cube.h"
#include "../Parallelepiped/Parallelepiped.h"

Render::Mesh Render::Cube::make(GEGraphics* context, Position3 pos, int size)
{
	return Parallelepiped::make(context, pos, Vector3(size, size, size));
}

Render::Mesh Render::Cube::make_independent(GEGraphics* context, Position3 pos, int size)
{
	return Parallelepiped::make_independent(context, pos, Vector3(size, size, size));
}
