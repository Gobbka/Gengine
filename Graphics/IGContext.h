#pragma once
#include "Render/d3d/Buffer/ConstantBuffer.h"
#include "Types/Types.h"

namespace Render
{
	enum class PrimitiveTopology
	{
		TRIANGLESTRIP,
		TRIANGLELIST
	};
	
	class IGContext
	{
	protected:
		IGContext(Core::GraphicsContext* context)
			: matrix_buffer(context),
			control_buffer(context,1,CBBindFlag_vs | CBBindFlag_ps)
		{}
	public:
		__declspec(align(16))
			struct MatrixBufferStruct
		{
			DirectX::XMMATRIX VPMatrix;
			DirectX::XMMATRIX ModelMatrix;
		};

		__declspec(align(16))
			struct ControlBufferStruct
		{
			Position2 offset = Position2(0, 0);
			float opacity = 1.f;
		};
		
	public:
		ConstantBuffer<MatrixBufferStruct> matrix_buffer;
		ConstantBuffer<ControlBufferStruct> control_buffer;

		virtual void set_topology(PrimitiveTopology topology) =0;
	};
}
