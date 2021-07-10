#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"
#include "elements/Panel/Panel.h"
#include "UIManager.h"
#include "InteractiveForm.h"

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
	
    auto* window = Core::WindowsManager::instance()->create_window(hInstance,800,600);
    window->show();

    auto* graphic = Core::GraphicsContext::new_context(window->hwnd());

    {
        RECT rect;
        GetClientRect(window->hwnd(), &rect);
        graphic->set_resolution(Surface(rect));
    }
	
    window->on_resize = [graphic](Surface size)
    {
        graphic->set_resolution(size);
    };

    auto* uicanvas = UI::UIManager::instance()->create_layer(graphic->get_2d_engine());
    auto* panel = new UI::Panel({ 0,0}, { 250,300 }, { 1.,0.3f,0.2f,1.f });
    uicanvas->add_element(panel);

    panel->onMouseEnter = [](UI::UIElementEventArgs args)
    {
        args->set_color({ .8f,.5f,.3f,1.f });
    };

    panel->onMouseLeave = [](UI::UIElementEventArgs args)
    {
        args->set_color({ .5f,.3f,.2f,1.f });
    };

    panel->onMouseDown = [uicanvas](UI::UIElementEventArgs args)
    {
        auto* button = (UI::Panel*)args;
        UI::UIManager::instance()->animator()->add_animation(new UI::Animation(0, 1.f, 1000, [button](float value)
            {
                button->set_alpha(value);
            }));
        uicanvas->drag_move(args);
    };

    panel->onMouseUp = [uicanvas](UI::UIElementEventArgs args)
    {
        uicanvas->drag_move(args);
    };
	
    graphic->append_2d_layer(uicanvas);

    window->on_wndproc = [](UINT msg, WPARAM wp, LPARAM lp)
    {
        UI::UIManager::instance()->window_proc(msg, wp, lp);
    };
	
    MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, nullptr,0, 0, PM_REMOVE))
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}

        graphic->clear();
        graphic->present();

        Sleep(10);
	}
	
    return 0;
}
