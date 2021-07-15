#pragma once
#include "WindowsWindow.h"

namespace Core
{
	class GraphicsContext;

	class Form : public WindowsWindow
	{
	private:
		GraphicsContext* _graphics;
	protected:
		Form(HINSTANCE hinst, UINT width, UINT height);
	};
}
