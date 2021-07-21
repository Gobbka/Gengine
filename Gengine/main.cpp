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

    

    std::wcout << lpCmdLine<<'\0';
	
    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
        UI::UIManager::instance()->window_proc(msg, wp, lp);

    	if(msg == WM_KEYDOWN)
    	{
    		if(wp == 0x57) // W
    		{
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(0,0, 0.5f));
    		}
    		if(wp == 0x53)
    		{
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(0, 0, -0.5f));
    		}
            if (wp == 0x44)
            {
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(0.5f, 0, 0));
            }
    		if(wp == 0x41)
    		{
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(-0.5f, 0, 0));
    		}
    		if(wp == VK_SPACE)
    		{
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(0, 0.5f, 0));
    		}
            if (wp == VK_CONTROL)
            {
                form->get_graphics_context()->main_camera()->transform.adjust_position(Position3(0, -0.5f, 0));
            }
    	}
			
    };

	
    MSG msg;
	while(true)
	{
		if(PeekMessage(&msg, nullptr,0, 0, PM_REMOVE))
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}
		
        form->force_draw();

        Sleep(10);
	}
}
