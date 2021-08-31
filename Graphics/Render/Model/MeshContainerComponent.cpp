#include "MeshContainerComponent.h"

Render::MeshContainerComponent::MeshContainerComponent()
	: transform({0,0,0})
{

}

void Render::MeshContainerComponent::add_mesh(Mesh mesh)
{
	meshes.push_back(mesh);
}
