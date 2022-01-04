#include "MeshRenderer.h"

Render::MeshRenderer::MeshRenderer(GETexture* texture, GETexture*normals)
	: texture(texture)
	, normals(normals)
	, transform(Position3::null())
{}

void Render::MeshRenderer::add_mesh(Mesh mesh)
{
	meshes.push_back(mesh);
}
