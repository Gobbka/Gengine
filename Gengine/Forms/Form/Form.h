#pragma once
#include "Window/WindowsWindow.h"
#include "Graphics/Scene.h"
#include "Types/Types.h"

namespace UI {
	class UIContext;
}

namespace Core
{
	class GraphicsContext;

	class Form : public WindowsWindow
	{

		GraphicsContext* _graphics;
		UI::UIContext* _ui_context;
		
	protected:
		void handle_resize(Surface rect) override;

		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		Render::Scene* main_scene;
		Color3XM background{ 0,0,0 };

		UI::UIContext* get_ui();
		GraphicsContext* get_graphics_context() const;

		void drag_move();
		void force_draw();

		virtual void update() PURE;
	};

}
