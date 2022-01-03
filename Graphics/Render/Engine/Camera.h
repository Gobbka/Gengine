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
		RenderTarget* _render_target;
		MaskEngine* _mask_engine;
		Core::GraphicsContext* _context;
	public:
		void clear(Color3XM color);
		void clear();
		
		void set_resolution(Surface new_resolution);
	public:
		Core::GraphicsContext* graphics_context();
		RenderTarget* get_target_view();
		MaskEngine* get_mask_engine() const;
	public:
		Camera& operator=(Camera&& other) noexcept;
		Camera(Camera&& other) noexcept;
		Camera(Core::GraphicsContext* context,RenderTarget*target);

		void bind() const;
	};
}
