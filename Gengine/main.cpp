#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"

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
