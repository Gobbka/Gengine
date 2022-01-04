#pragma once
#include "Window/WindowsWindow.h"
#include "Graphics/Scene.h"
#include "Types/Types.h"

namespace UI {
	class UIContext;
}

namespace Core
{
	class DX11Graphics;
}

namespace GE
{

	class Form : public Window
	{
		Core::DX11Graphics* _graphics;
		UI::UIContext* _ui_context;
		
	protected:
		void handle_resize(Surface rect) override;

		Form(const wchar_t*name, HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		Render::Scene* main_scene;

		UI::UIContext* get_ui();
		Core::DX11Graphics* get_graphics_context() const;

		void drag_move();
		void force_draw();

		virtual void update() PURE;
	};

}
