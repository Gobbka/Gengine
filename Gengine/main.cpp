#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"
#include "Canvas/Objects/Rectangle/Rectangle.h"


int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{

    auto* window = Core::WindowsManager::instance()->create_window(hInstance,800,600);
    window->show();

    auto* graphic = Core::GraphicsContext::new_context(window->hwnd());

    {
        RECT rect;
        GetClientRect(window->hwnd(), &rect);
        graphic->set_resolution(Surface(rect));
    }

    auto* layer = graphic->create_2d_layer();
	
    window->on_resize = [graphic](Surface size)
    {
        graphic->set_resolution(size);
    };
	
    auto* rectangle = new Canvas::Rectangle(Color4(RGB_TO_FLOAT(120,120,120),1.f),Position2(1,-1),Surface(390,100));

    AllocConsole();
    freopen("CONIN$", "r", stdin);
    freopen("CONOUT$", "w", stdout);
    freopen("CONOUT$", "w", stderr);
	
    layer->add_object(new Canvas::Rectangle(Color4(RGB_TO_FLOAT(30, 120, 30), 1.f), Position2(1, -1), Surface(100, 390)));
    layer->add_object(rectangle);
	
    MSG msg;
    while (GetMessage(&msg,nullptr,0,0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        graphic->clear();
        graphic->present();
    }
	
    return 0;
}
