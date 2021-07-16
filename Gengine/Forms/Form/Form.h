#pragma once
#include "WindowsWindow.h"

namespace Core
{
	class GraphicsContext;

	class Form : public WindowsWindow
	{
	private:
		GraphicsContext* _graphics;

		void handle_resize(RECT* rect) override;
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
		virtual ~Form();
	public:
		GraphicsContext* get_graphics_context() const;
	};
}
