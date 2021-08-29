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
	class MaskEngine;
	class MeshContainerComponent;
	class RenderTarget;

	class __declspec(dllexport) WorldViewer
	{
		
	protected:
		void update_position();
		void update_rotation();
		
	private:
		DirectX::XMMATRIX create_view_matrix();
	 	static DirectX::XMMATRIX create_projection_matrix(Surface resolution,float fov,float farz,float scale=1.f);
	private:
		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
		DirectX::XMVECTOR _xm_camPosition;
	protected:
		RenderTarget* render_target;
		MaskEngine* mask_engine;
		
		Core::Transform _transform;
	private:
		float _fov = 45.f;
		float _scale = 1.f;
		float _far_z = 120.f;
		Surface _resolution;

	protected:
		Core::GraphicsContext* context;

	protected:
		WorldViewer(Core::GraphicsContext* context, RenderTarget* target);

	public:
		void view(MeshContainerComponent* model);
		
		void set_scale(float scale);
		void set_fov(float fov);
		void set_farz(float farz);

		inline MaskEngine* get_mask_engine();

		Core::GraphicsContext* graphics_context();

		RenderTarget* get_render_target();
		Surface get_view_resolution();
		void set_view_resolution(Surface surface);

		DirectX::XMMATRIX world_to_screen_matrix();

		void bind();
	};
}
