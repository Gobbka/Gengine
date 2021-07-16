#include "Form.h"

#include "Graphics.h"
#include "WindowsManager.h"

void Core::Form::handle_resize(Surface rect)
{
    _graphics->set_resolution(rect);
    WindowsWindow::handle_resize(rect);
}

Core::Form::Form(HINSTANCE hinst, UINT width, UINT height)
	: WindowsWindow(hinst,width,height)
{
	WindowsManager::instance()->register_window(this);
	
	_graphics = GraphicsContext::new_context(WindowsWindow::hwnd());

    {
        RECT rect;
        GetClientRect(hwnd(), &rect);
        _graphics->set_resolution(Surface(rect));
    }
}

Core::Form::~Form()
{
	WindowsManager::instance()->remove_window(this);
}

Core::GraphicsContext* Core::Form::get_graphics_context() const
{
    return _graphics;
}

void Core::Form::drag_move()
{
    ReleaseCapture();
    SendMessage(hwnd(), WM_NCLBUTTONDOWN, HTCAPTION, 0);
}

void Core::Form::force_draw()
{
    _graphics->clear(Color3(RGB_TO_FLOAT(background.r,background.g,background.b)));
    
    _graphics->present();
}
