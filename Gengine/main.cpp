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

Render::Material* material;

void bmp_test(Core::GraphicsContext* context)
{
    std::ifstream ifs("228.png", std::ios::in | std::ios::binary | std::ifstream::ate);

    assert(ifs.is_open());

    auto size = (size_t)ifs.tellg();
    ifs.seekg(0);

    auto* ptr = new char[size + 1];
    ptr[size] = '\0';
    ifs.read(ptr, size);
	
    auto* fmemory = FreeImage_OpenMemory((BYTE*)ptr, size);
    auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory);


    auto*nigger = FreeImage_GetBits(bitmap);
    material = context->create_material({ (float)FreeImage_GetWidth(bitmap) ,(float)FreeImage_GetHeight(bitmap) }, (char*)nigger);

	
    FreeImage_CloseMemory(fmemory);
	
    delete[] ptr;
}

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

    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    auto* graphic = form->get_graphics_context();

    //panel->onMouseDown = [&](UI::UIElementEventArgs args)
    //{
    //    //form->drag_move();
    //    uicanvas->drag_move(args);
    //};

    form->on_wndproc = [](UINT msg, WPARAM wp, LPARAM lp)
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
		
        //graphic->set_texture(texture);
        form->force_draw();

        Sleep(10);
	}
}
