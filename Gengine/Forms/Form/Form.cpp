#include "Form.h"

#include "Graphics.h"
#include "WindowsManager.h"
#include "Render/Engine/Camera.h"

void Core::Form::handle_resize(Surface rect)
{
    _graphics->set_resolution(rect);
    WindowsWindow::handle_resize(rect);
}

void Core::Form::draw_frame()
{
    //main_camera->render();
}

Core::Form::Form(HINSTANCE hinst, UINT width, UINT height)
	: WindowsWindow(hinst,width,height)
{
	WindowsManager::instance()->register_window(this);
	
	_graphics = GraphicsContext::new_context(WindowsWindow::hwnd(),WindowsWindow::size());
    main_camera = _graphics->create_camera(nullptr);
    _graphics->bind_main_camera(main_camera);
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
    _graphics->make_frame();
	
    //main_camera->clear(Color3(0.1f, 0.1f, 0.1f));
    draw_frame();
	
    _graphics->present_frame();
}
