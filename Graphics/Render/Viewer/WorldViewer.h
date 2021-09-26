#pragma once
#include <DirectXMath.h>

#include "Types/Transform.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class MaskEngine;
	class MeshRenderer;
	class RenderTarget;

	enum class WVProjectionType
	{
		Orthographic,
		Perspective,
	};
	
	class __declspec(dllexport) WorldViewer
	{
		
	protected:
		void update_position();
		void update_rotation();
		
	private:
		DirectX::XMMATRIX create_view_matrix();
	 	static DirectX::XMMATRIX create_projection_matrix(WVProjectionType projection,Surface resolution,float fov,float farz,float scale=1.f);
	private:
		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
	protected:
		RenderTarget* render_target;
		MaskEngine* mask_engine;
		
		Core::Transform _transform;
		WVProjectionType projection = WVProjectionType::Perspective;
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
		void set_projection_type(WVProjectionType type);
		void set_scale(float scale);
		void set_fov(float fov);
		void set_farz(float farz);

		inline MaskEngine* get_mask_engine();

		Core::GraphicsContext* graphics_context();

		RenderTarget* get_render_target();
		Surface get_view_resolution();
		void set_view_resolution(Surface surface);

		Vector3 point_to_world(Vector2 screen_coordinate);
		DirectX::XMMATRIX world_to_screen_matrix();

		void bind();
	};
}
