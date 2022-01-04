#pragma once
#include <DirectXMath.h>

#include "Types/Transform.h"
#include "Types/Types.h"

namespace Render
{
	class MeshRenderer;

	enum class WVProjectionType
	{
		Orthographic,
		Perspective,
	};
	
	class __declspec(dllexport) WorldViewer
	{
	private:
		DirectX::XMMATRIX create_view_matrix();
	 	static DirectX::XMMATRIX create_projection_matrix(WVProjectionType projection,Surface resolution,float fov,float farz,float scale=1.f);
		DirectX::XMMATRIX create_projection_matrix() const;
	protected:
		Core::Transform _transform;
		WVProjectionType projection = WVProjectionType::Perspective;
	private:
		float _fov = 45.f;
		float _scale = 1.f;
		float _far_z = 120.f;
		Surface _resolution;

		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
	public:
		explicit WorldViewer(Surface resolution = Surface(0, 0));
		WorldViewer(WorldViewer& other);

		void set_projection_type(WVProjectionType type);
		void set_scale(float scale);
		void set_fov(float fov);
		void set_farz(float farz);

		Surface get_view_resolution() const;
		void set_view_resolution(Surface surface);

		inline DirectX::XMMATRIX world_to_screen_matrix() const;
		inline DirectX::XMMATRIX view_matrix() const;
		inline DirectX::XMMATRIX projection_matrix() const;
		inline DirectX::XMMATRIX rotation_matrix() const;

		void set_position(Position3 pos);
		void adjust_position(Position3 pos);
		void adjust_position_relative(Position3 pos);

		void set_rotation(Vector3 quat);
		void adjust_rotation(Vector3 rot);
	};
}
