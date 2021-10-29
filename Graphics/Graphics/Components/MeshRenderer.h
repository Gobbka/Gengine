#pragma once
#include <vector>
#include "../Mesh.h"
#include "Types/Transform.h"

namespace Render
{
	class Texture;
	
	class __declspec(dllexport) MeshRenderer
	{
	public:
		Texture* texture;
		Texture* normals;

		std::vector<Mesh> meshes;
		Core::Transform transform;

		MeshRenderer() = delete;
		MeshRenderer(Texture* texture,Texture*normals=nullptr);

		void add_mesh(Mesh mesh);
	};
}
