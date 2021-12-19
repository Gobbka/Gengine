#include "Form.h"

#include "Graphics.h"
#include "UIContext.h"
#include "Window/WindowsManager.h"
#include "../../resource.h"

void GE::Form::handle_resize(Surface rect)
{
    _graphics->set_resolution(rect);
    Window::handle_resize(rect);
}

GE::Form::Form(const wchar_t*name,HINSTANCE hinst, UINT width, UINT height)
	: Window(name, hinst, width, height,LoadIcon(hinst,MAKEINTRESOURCE(IDI_ICON1)))
	, _graphics(Graphics_CreateContext(hwnd()))
	, _ui_context(nullptr)
	, main_scene(_graphics->create_scene_3d())
{
    _ui_context = new UI::UIContext(_graphics, main_scene);
	main_scene->set_main_camera(main_scene->create_camera(_graphics->get_render_target_view()));
    auto&pipeline = main_scene->render_pipeline();
    //pipeline.clear(Render::PassStep::draw);
	pipeline.clear(Render::PassStep::probe);
	pipeline.clear(Render::PassStep::begin);
}

GE::Form::~Form()
{
    delete _ui_context;
    delete _graphics;
	WindowsManager::instance()->remove_window(this);
}

UI::UIContext* GE::Form::get_ui()
{
    return _ui_context;
}

Core::GraphicsContext* GE::Form::get_graphics_context() const
{
    return _graphics;
}

void GE::Form::drag_move()
{
    ReleaseCapture();
    SendMessage(hwnd(), WM_NCLBUTTONDOWN, HTCAPTION, 0);
}

void GE::Form::force_draw()
{
    if (size().width == 0.f)
    {
        Sleep(17);
        return;
    }

    _graphics->make_frame();
    _graphics->present_frame();
}
