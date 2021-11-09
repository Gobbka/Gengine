#include "Form.h"

#include "Graphics.h"
#include "UIContext.h"
#include "Window/WindowsManager.h"
#include "Render/Engine/Camera.h"

void Core::Form::handle_resize(Surface rect)
{
    _graphics->set_resolution(rect);
    WindowsWindow::handle_resize(rect);
}

void Core::Form::draw_frame()
{
}

Core::Form::Form(HINSTANCE hinst, UINT width, UINT height)
	: WindowsWindow(hinst,width,height),
	_graphics(GraphicsContext::new_context(WindowsWindow::hwnd(), WindowsWindow::size())),
	main_scene(_graphics->create_scene())
{
    _uicontext = new UI::UIContext(_graphics);
    main_scene->set_main_camera(main_scene->create_camera(_graphics->get_render_target_view()));
}

Core::Form::~Form()
{
	WindowsManager::instance()->remove_window(this);
}

UI::UIContext* Core::Form::get_ui()
{
    return _uicontext;
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
    if (WindowsWindow::size().width == 0.f)
    {
        Sleep(17);
        return;
    }

    _graphics->make_frame();
	
    draw_frame();
	
    _graphics->present_frame();
}
