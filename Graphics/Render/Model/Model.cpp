#include "Model.h"

Render::Model::Model()
	: transform({0,0,0})
{

}

void Render::Model::add_mesh(Mesh* mesh)
{
	_meshes.push_back(mesh);
}

void Render::Model::draw()
{	
	for(auto* mesh : _meshes)
	{
		mesh->draw();
	}
}
