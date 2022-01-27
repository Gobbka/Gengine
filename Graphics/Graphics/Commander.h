#pragma once
#include "../Render/Common/GraphicsCommon.h"

namespace Render {
	struct Mesh;
	class PixelShader;

	class Commander
	{
		GEGraphics* _gfx;
		PixelShader* _normals_ps;
		PixelShader* _normals_texture_ps;
	public:
		Commander(GEGraphics* gfx);

		void nm_begin();
		void nm_solid_mode();
		void nm_texture_mode(GETexture*normals);

		void draw_mesh(Mesh& mesh);
	};
}