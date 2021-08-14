#pragma once
#include <DirectXMath.h>



#include "../d3d/Buffer/ConstantBuffer.h"
#include "Types/Transform.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Model;
	class RenderTarget;

	class __declspec(dllexport) WorldViewer
	{
		__declspec(align(16))
			struct
		{
			DirectX::XMMATRIX _MVPMatrix;
		} _matrix_buffer_struct;
		
	protected:
		void update_position();
		void update_rotation();
		
	private:
		DirectX::XMMATRIX create_view_matrix();
	 	static DirectX::XMMATRIX create_projection_matrix(Surface resolution,float fov,float scale=1.f);
	private:
		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
		DirectX::XMVECTOR _xm_camPosition;
	protected:
		RenderTarget* render_target;
		Core::Transform _transform;

		ConstantBuffer matrix_buffer;
	private:
		float _fov = 90.f;
		float _scale = 1.f;
		Surface _resolution;

	protected:
		Core::GraphicsContext* context;

	protected:
		WorldViewer(Core::GraphicsContext* context, RenderTarget* target);

		void view(Model* model);
	public:
		void set_scale(float scale);
		void set_fov(float fov);

		Core::GraphicsContext* graphics_context();
		
		Surface get_view_resolution();
	};
}
