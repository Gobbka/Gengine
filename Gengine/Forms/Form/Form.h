#pragma once
#include "WindowsWindow.h"
#include "Ecs/Ecs.h"
#include "Types/Types.h"

namespace UI {
	class UIContext;
}

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
		UI::UIContext* _uicontext;
	protected:
		ECS::Entity* main_camera;
		void handle_resize(Surface rect) override;

		virtual void draw_frame();
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		UI::UIContext* get_ui();
		
		Color3 background{0,0,0};
		
		GraphicsContext* get_graphics_context() const;

		void drag_move();
		
		void force_draw();

		virtual void update() PURE;
	};
}
