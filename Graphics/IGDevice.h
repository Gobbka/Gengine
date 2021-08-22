#pragma once
#include "Ecs/Ecs.h"

namespace Render
{
	class RenderTarget;

	class __declspec(dllexport) IGDevice
	{
	public:
		virtual ~IGDevice() = default;
		/// <summary>
		/// create and returns camera pointer
		/// </summary>
		/// <param name="target">pointer to render target.If nullptr passed,camera will create from swap chain</param>
		/// <returns></returns>
		virtual ECS::Entity* create_camera(Render::RenderTarget* target) =0;
		
		virtual ECS::Entity* create_model() =0;
	};
}

