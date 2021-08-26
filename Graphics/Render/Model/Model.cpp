#include "Model.h"

#include "../Events/RenderEvent.h"
#include "Ecs/Ecs.h"

Render::Model::Model()
	: transform({0,0,0})
{

}

void Render::Model::add_mesh(Mesh mesh)
{
	_meshes.push_back(mesh);
}

void Render::Model::draw(DrawEvent3D event3d)
{	
	for(auto mesh : _meshes)
	{
		mesh.draw(event3d);
	}
}
