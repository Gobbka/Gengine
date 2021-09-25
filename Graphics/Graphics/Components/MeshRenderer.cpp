#include "MeshRenderer.h"
#include "../../Render/I3DObject/Mesh.h"

Render::MeshRenderer::MeshRenderer(Texture* texture)
	: transform(Position3::null())
{
	this->texture = texture;
}

void Render::MeshRenderer::add_mesh(Mesh mesh)
{
	meshes.push_back(mesh);
}
