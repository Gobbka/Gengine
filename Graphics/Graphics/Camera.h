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
		GEGraphics* _context;
	public:
		void clear(Color3XM color);
		void clear();
		
		void set_resolution(Surface new_resolution);

		GEGraphics* graphics_context();
		DX11RenderTarget* get_target_view();
		GEMaskEngine* get_mask_engine() const;

		Camera& operator=(Camera&& other) noexcept;
		Camera(Camera&& other) noexcept;
		Camera(GEGraphics* context, DX11RenderTarget*target);

		void bind() const;
	};
}
