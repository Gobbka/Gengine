#pragma once
#include "../../../Render/d3d/Buffer/ConstantBuffer.h"
#include "../IPass/IPass.h"

namespace Render
{
	class DirectionLightPass : IPass
	{
		__declspec(align(16))
			struct MatrixBufferStruct
		{
			DirectX::XMMATRIX VPMatrix;
		};

		ConstantBuffer<MatrixBufferStruct> _matrix_buffer;

		explicit DirectionLightPass(Core::GraphicsContext*context);
		
		void execute(Core::GraphicsContext* context) override;
	};
}
