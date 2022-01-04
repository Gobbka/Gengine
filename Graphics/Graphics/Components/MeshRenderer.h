#pragma once
#include <vector>
#include "../Mesh.h"
#include "Types/Transform.h"
#include "../../Render/Common/Texture.h"

namespace Render
{
	
	class __declspec(dllexport) MeshRenderer
	{
	public:
		GETexture* texture;
		GETexture* normals;

		std::vector<Mesh> meshes;
		Core::Transform transform;

		MeshRenderer() = delete;
		MeshRenderer(GETexture* texture, GETexture*normals=nullptr);

		void add_mesh(Mesh mesh);
	};
}
