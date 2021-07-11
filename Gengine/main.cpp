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
    auto* panel = new UI::Panel({ -1,1}, { 1,1 }, { RGB_TO_FLOAT(38,37,37),1.f });
    uicanvas->add_element(panel);
    panel->set_texture(nullptr);
	
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

        graphic->clear(Color3(RGB_TO_FLOAT(24,24,24)));
        graphic->present();

        Sleep(10);
	}
}
