#pragma once
#include "WindowsManager.h"
#include "WindowsWindow.h"
#include "Graphics/Scene.h"
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
		void handle_resize(Surface rect) override;

		virtual void draw_frame();
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		Render::Scene* main_scene;

		UI::UIContext* get_ui();
		
		Color3XM background{0,0,0};
		
		GraphicsContext* get_graphics_context() const;

		void drag_move();
		
		void force_draw();

		virtual void update() PURE;
	};

}
