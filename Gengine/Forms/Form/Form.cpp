#include "Form.h"

#include "Graphics.h"

Core::Form::Form(HINSTANCE hinst, UINT width, UINT height)
	: WindowsWindow(hinst,width,height)
{
	_graphics = Core::GraphicsContext::new_context(WindowsWindow::hwnd());
	
}
