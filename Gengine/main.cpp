#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"

#include "FreeImage.h"
#include "Render/d3d/Buffer/Texture.h"

#include <fstream>


#include "UIManager.h"
#include "Drivers/PNGImageDriver.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

extern Render::Material* load_png(const wchar_t* path);

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

    std::wcout << lpCmdLine<<'\n';
	
    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
        UI::UIManager::instance()->window_proc(msg, wp, lp);
    };

    auto* material = load_png(L"assets\\mine4ok.png");
    
	
    auto cube = Render::Cube(Position3::null(), form->get_graphics_context());
    cube.set_texture(form->get_graphics_context()->create_texture(material));
	
    form->get_graphics_context()->worldspace()->add_object(&cube);
	
    MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, nullptr,0, 0, PM_REMOVE))
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}

        form->update();
        form->force_draw();
		
        Sleep(10);
	}
}
