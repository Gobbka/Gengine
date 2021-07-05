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

    auto* window = Core::WindowsManager::instance()->create_window(hInstance);
    window->show();

    auto* graphic = Core::GraphicsContext::new_context(window->hwnd());

    auto* layer = graphic->create_2d_layer();

    Canvas::Rectangle* rectangle = new Canvas::Rectangle(Color4(RGB_TO_FLOAT(120,120,120),1.f),Position2(-50,50),Surface(500,500));

    layer->add_object(rectangle);
	
    MSG msg;

    while (GetMessage(&msg,nullptr,0,0)>0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        graphic->clear();
        graphic->present();
    }
	
    return 0;
}
