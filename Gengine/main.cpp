#include <Windows.h>
#include "WindowsWindow.h"
#include "Graphics.h"

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{

    auto* window = new Core::WindowsWindow(hInstance);
    window->show();

    MSG msg;

    auto* graphic = Core::GraphicsContext::new_context(window->hwnd());
	
    while (GetMessage(&msg,nullptr,0,0)>0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);

        graphic->present();
    }
	
    return 0;
}