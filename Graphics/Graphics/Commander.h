#pragma once
#include <DirectXMath.h>
#include "../Render/Common/GraphicsCommon.h"

namespace Render {
	class Camera;
	struct Mesh;
	class PixelShader;
	template<typename T>
	class ConstantBuffer;

	class Commander
	{
		__declspec(align(16))
			struct MVPStruct
		{
			DirectX::XMMATRIX MVPMatrix;
			DirectX::XMMATRIX ModelMatrix;
		};


		GEGraphics* _gfx;
		PixelShader* _normals_ps;
		PixelShader* _normals_texture_ps;
		ConstantBuffer<MVPStruct>* _mvp_buffer;
		DirectX::XMMATRIX _vp_matrix;
	public:
		Commander(GEGraphics* gfx);

		void nm_begin();
		void nm_solid_mode();
		void nm_texture_mode(GETexture*normals);

		void render_begin();
		void bind_camera(Camera* camera);
		void bind_camera_matrix(Camera* camera);
		void draw_mesh(Mesh& mesh);
		void draw_mesh(Mesh& mesh, DirectX::XMMATRIX model_matrix);
	};
}