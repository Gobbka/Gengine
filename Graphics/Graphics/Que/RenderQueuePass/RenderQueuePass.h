#pragma once
#include <DirectXMath.h>


#include "../../../Render/d3d/Buffer/ConstantBuffer.h"
#include "../IPass/IPass.h"
#include "Ecs/Ecs.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Camera;
	class VertexShader;
	class PixelShader;
	class MaskEngine;
	class RenderTarget;

	class ClearPass : public IPass
	{
		void execute(Core::GraphicsContext* context) override;
	};
	
	class __declspec(dllexport) RenderQueuePass : public IPass
	{
		__declspec(align(16))
		struct MatrixBufferStruct
		{
			DirectX::XMMATRIX VPMatrix;
		};

		__declspec(align(16))
		struct ControlBufferStruct
		{
			Position2 offset = Position2(0, 0);
			float opacity = 1.f;
		};

		ConstantBuffer<MatrixBufferStruct> _matrix_buffer;
		ConstantBuffer<ControlBufferStruct> _control_buffer;
		
		void render_camera_3d(ECS::ComponentHandle<Camera> camera, ECS::World* world);
		void render_camera_2d(ECS::ComponentHandle<Camera> camera);

		void render_model(ECS::ComponentHandle<Camera> camera,ECS::ComponentHandle<Model> model,DirectX::XMMATRIX matrix);
		inline void render_camera(ECS::ComponentHandle<Camera> camera, ECS::World* world);
	public:
		RenderQueuePass(Core::GraphicsContext* context);
		
		void execute(Core::GraphicsContext* context) override;
	};
}
