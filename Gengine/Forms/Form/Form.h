#pragma once
#include "WindowsWindow.h"
#include "Types/Types.h"

namespace Render {
	class RenderQueuePass;
	class Camera;
}

namespace Core
{
	class GraphicsContext;

	class Form : public WindowsWindow
	{
	private:
		GraphicsContext* _graphics;
	protected:
		Render::Camera* main_camera;
		void handle_resize(Surface rect) override;

		virtual void draw_frame();
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		Color3 background{0,0,0};
		
		GraphicsContext* get_graphics_context() const;

		void drag_move();
		
		void force_draw();

		virtual void update() PURE;
	};
}
