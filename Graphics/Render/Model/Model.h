#pragma once
#include <vector>

#include "../I3DObject/Object3D.h"

namespace Render
{
	struct DrawEvent3D;
	typedef Object3D Mesh;
	
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
