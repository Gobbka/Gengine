#pragma once
#include <DirectXMath.h>


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
	protected:
		void update_position();
		void update_rotation();
		
	private:
		DirectX::XMMATRIX create_view_matrix();
		DirectX::XMMATRIX create_proj_matrix();
	protected:
		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
		DirectX::XMVECTOR _xm_camPosition;

		Core::Transform _transform;
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

		Surface get_view_resolution();
	};
}
