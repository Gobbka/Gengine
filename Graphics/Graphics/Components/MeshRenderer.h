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

		std::vector<Mesh> meshes;
		Core::Transform transform;

		MeshRenderer() = delete;
		explicit MeshRenderer(Texture* texture);

		void add_mesh(Mesh mesh);
	};
}
