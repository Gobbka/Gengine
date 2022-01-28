#pragma once
#include <DirectXMath.h>
#include "../Render/Common/GraphicsCommon.h"

namespace Render {
	class Camera;
	struct Mesh;
	class PixelShader;
	template<typename T>
	class ConstantBuffer;

	__declspec(align(16))
	struct MVPStruct
	{
		GEMatrix MVPMatrix;
		GEMatrix ModelMatrix;
	};

	class Commander
	{

		GEGraphics* _gfx;
		PixelShader* _normals_ps;
		PixelShader* _normals_texture_ps;
		ConstantBuffer<MVPStruct>* _mvp_buffer;
		GEMatrix _vp_matrix;
	public:
		Commander(GEGraphics* gfx);

		void nm_begin();
		void nm_solid_mode();
		void nm_texture_mode(GETexture*normals);

		void render_begin();
		void bind_camera(Camera* camera);
		void bind_camera(Camera* camera,GEMatrix vp_matrix);
		void draw_mesh(Mesh& mesh);
		void draw_mesh(Mesh& mesh,GEMatrix model_matrix);
	};
}