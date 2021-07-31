#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../d3d/Buffer/ConstantBuffer.h"
#include "../I3DObject/Object3D.h"
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
			DirectX::XMMATRIX _viewMatrix;
		} _matrix_buffer_struct;

		__declspec(align(16))
			struct
		{
			DirectX::XMMATRIX _viewMatrix;
		} _matrix2d_buffer_struct;
		
		__declspec(align(16))
		struct
		{
			Position2 offset = Position2(0,0);
			float opacity = 1.f;
		} _control_buffer_struct;

		ConstantBuffer* matrix_buffer;
		ConstantBuffer* matrix2d_buffer;
		ConstantBuffer* control_buffer;

		BlendEngine* _blendEngine;
		MaskEngine*  _maskEngine;

		Core::Transform _transform;

		DirectX::XMVECTOR _xm_camPosition;
		DirectX::XMVECTOR _xm_lookAt;
		
		float _fov = 90.f;

		std::vector<Canvas::Canvas2DLayer*> _canvas2DLayers;
	private:
		void update_position();
		void draw_object(Object3D* object);
		
		DirectX::XMMATRIX create_view_matrix();
		DirectX::XMMATRIX create_proj_matrix();
		
		DirectX::XMMATRIX _projectionMatrix;
		DirectX::XMMATRIX _viewMatrix;
		
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

		void present();
	};
}
