#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../Layer/ILayer.h"
#include "Types/Transform.h"

struct Surface;

namespace Render
{
	class Cube;
	class MaskEngine;
	class BlendEngine;

	class __declspec(dllexport) Camera
	{
	private:
		Core::GraphicsContext* _context;

		__declspec(align(16))
		struct
		{
			float width;
			float height;
			float alpha;
		} _b0_constant_buffer_struct;

		__declspec(align(16))
		struct
		{
			DirectX::XMMATRIX _viewMatrix;
		} _b1_constant_buffer_struct;

		ConstantBuffer* b0_buffer;
		ConstantBuffer* matrix_buffer;

		BlendEngine* _blendEngine;
		MaskEngine*  _maskEngine;

		Core::Transform _transform;
		Core::Quaternion3 _rotation;

		DirectX::XMVECTOR _xm_camPosition;
		DirectX::XMVECTOR _xm_lookAt;
		
		float _fov = 90.f;
		
		Cube* _cube;

		std::vector<Canvas::Canvas2DLayer*> _canvas2DLayers;
	private:
		void update_position();
		
		DirectX::XMMATRIX create_view_matrix();


		DirectX::XMVECTOR _forward_vector;
		DirectX::XMVECTOR _backward_vector;
		DirectX::XMVECTOR _right_vector;
		DirectX::XMVECTOR _left_vector;
		DirectX::XMVECTOR _up_vector;
	public:
		void set_position(Position3 pos);
		void adjust_position(Position3 pos);
		void adjust_position_relative(Position3 pos);
		
		void set_rotation(Core::Quaternion3 quat);
		void adjust_rotation(Vector3 rot);
		
		void set_resolution(Surface new_resolution);
		void set_alpha(float alpha);

		Canvas::Canvas2DLayer* create_canvas_2d();
		void register_canvas_2d(Canvas::Canvas2DLayer* layer);
	public:
		Core::GraphicsContext* graphics_context();
		ID3D11DeviceContext* context() const;
		ID3D11Device* device() const;
		ID3D11RenderTargetView* get_target_view() const;
		MaskEngine* mask_engine() const;
		BlendEngine* blend_engine() const;

		Surface get_screen_resolution() const;
	public:
		
		Camera(Core::GraphicsContext* context);

		void present(DrawEvent* event);
	};
}
