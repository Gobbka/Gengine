#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"
#include "elements/Panel/Panel.h"
#include "UIManager.h"
#include "InteractiveForm.h"
#include "Drivers/BMPImageDriver.h"
#include "FreeImage.h"
#include "Render/d3d/Buffer/Texture.h"

#include <fstream>

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

    auto* graphic = form->get_graphics_context();

    auto* uicanvas = UI::UIManager::instance()->create_layer(graphic->main_camera());
    auto* panel = new UI::Panel({ 0,0}, { 100,150 }, { RGB_TO_FLOAT(38,37,37),1.f });
    uicanvas->add_element(panel);

    bmp_test(graphic);
    auto* texture = graphic->create_texture(material);
    panel->set_texture(texture);

    panel->onMouseDown = [&](UI::UIElementEventArgs args)
    {
        form->drag_move();
        //uicanvas->drag_move(args);
    };

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

        graphic->clear(Color3(RGB_TO_FLOAT(24,24,24)));
        graphic->set_texture(texture);
        graphic->present();

        Sleep(10);
	}
}
