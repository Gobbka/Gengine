#pragma once
#include <vector>

#include "../I3DObject/Mesh.h"

namespace Render
{
	struct DrawEvent3D;
	
	class __declspec(dllexport) MeshContainerComponent
	{
	public:
		std::vector<Mesh> meshes;
		Core::Transform transform;
		
		MeshContainerComponent();

		void add_mesh(Mesh mesh);
		
		void draw(DrawEvent3D event3d);
		
	};
}
