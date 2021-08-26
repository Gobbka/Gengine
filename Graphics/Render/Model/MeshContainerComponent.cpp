#include "MeshContainerComponent.h"

#include "../Events/RenderEvent.h"
#include "Ecs/Ecs.h"

Render::MeshContainerComponent::MeshContainerComponent()
	: transform({0,0,0})
{

}

void Render::MeshContainerComponent::add_mesh(Mesh mesh)
{
	meshes.push_back(mesh);
}

void Render::MeshContainerComponent::draw(DrawEvent3D event3d)
{	
	for(auto mesh : meshes)
	{
		mesh.draw(event3d);
	}
}
