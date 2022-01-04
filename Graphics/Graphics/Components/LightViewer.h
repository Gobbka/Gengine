#pragma once
#include "../../Render/Common/RenderTarget.h"

namespace Render
{
	struct __declspec(dllexport) LightViewer final
	{
		GERenderTarget normals_map;
		GERenderTarget light_map;

		LightViewer(Core::DX11Graphics*context,Surface resolution)
			: normals_map(context,resolution),
			light_map(context,resolution)
		{
			normals_map.clear_color = { .5f,.5f,.5f,1.f };
		}

		LightViewer(LightViewer&& other) noexcept
			: normals_map(std::move(other.normals_map))
		    , light_map(std::move(other.light_map))
		{}

		LightViewer& operator=(LightViewer&&other) noexcept
		{
			normals_map = std::move(other.normals_map);
			light_map = std::move(other.light_map);
			return *this;
		}
	};
}
