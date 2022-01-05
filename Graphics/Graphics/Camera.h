#pragma once
#include "../Render/Common/GraphicsCommon.h"
#include "../Render/Viewer/WorldViewer.h"

namespace Render
{
	class __declspec(dllexport) Camera : public WorldViewer
	{
		GEBlendEngine* _blendEngine;
		DX11RenderTarget* _render_target;
		GEMaskEngine* _mask_engine;
		GEGraphics* _graphics;
	public:
		void clear(Color3XM color) const;
		void clear() const;
		
		void set_resolution(Surface new_resolution);

		GEGraphics* get_graphics() const;
		DX11RenderTarget* get_target_view() const;
		GEMaskEngine* get_mask_engine() const;

		Camera& operator=(Camera&& other) noexcept;
		Camera(Camera&& other) noexcept;
		Camera(GEGraphics* graphics, DX11RenderTarget*target);

		void bind() const;
	};
}
