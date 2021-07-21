#pragma once
#include "WindowsWindow.h"
#include "Types/Types.h"
namespace Core
{
	class GraphicsContext;

	class Form : public WindowsWindow
	{
	private:
		GraphicsContext* _graphics;
	protected:
		void handle_resize(Surface rect) override;
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		Color3 background{0,0,0};
		
		GraphicsContext* get_graphics_context() const;

		void drag_move();

		void force_draw();
	};
}
