#pragma once
#include <vector>

#include "../I3DObject/Mesh.h"

namespace Render
{
	struct DrawEvent3D;
	
	class __declspec(dllexport) Model
	{
	private:
		std::vector<Mesh*> _meshes;
	public:
		Core::Transform transform;
		
		Model();

		void add_mesh(Mesh* mesh);
		
		void draw(DrawEvent3D event3d);
	};
}
