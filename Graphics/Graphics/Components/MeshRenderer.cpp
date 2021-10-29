#include "MeshRenderer.h"

Render::MeshRenderer::MeshRenderer(Texture* texture,Texture*normals)
	: texture(texture)
	, normals(normals)
	, transform(Position3::null())
{}

void Render::MeshRenderer::add_mesh(Mesh mesh)
{
	meshes.push_back(mesh);
}
