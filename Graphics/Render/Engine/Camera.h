#pragma once
#include "../Common/GraphicsCommon.h"
#include "../Viewer/WorldViewer.h"

struct Surface;

namespace Render
{

	class __declspec(dllexport) Camera : public WorldViewer
	{
	private:
		GEBlendEngine* _blendEngine;
		DX11RenderTarget* _render_target;
		GEMaskEngine* _mask_engine;
		Core::GraphicsContext* _context;
	public:
		void clear(Color3XM color);
		void clear();
		
		void set_resolution(Surface new_resolution);
	public:
		Core::GraphicsContext* graphics_context();
		DX11RenderTarget* get_target_view();
		GEMaskEngine* get_mask_engine() const;
	public:
		Camera& operator=(Camera&& other) noexcept;
		Camera(Camera&& other) noexcept;
		Camera(Core::GraphicsContext* context, DX11RenderTarget*target);

		void bind() const;
	};
}
