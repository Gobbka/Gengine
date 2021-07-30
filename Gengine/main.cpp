#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"

#include "FreeImage.h"
#include "Render/d3d/Buffer/Texture.h"

#include <fstream>

#include "PhysicsModule.h"
#include "UIManager.h"
#include "Drivers/PNGImageDriver.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

#include <assimp/importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

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

    Assimp::Importer importer;
    auto*scene = importer.ReadFile("assets\\gun.obj",aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
    assert(scene != nullptr);

	for(UINT i = 0;i < scene->mRootNode->mNumMeshes;i++)
	{
		
	}
	
    auto* material = load_png(L"assets\\mine4ok.png");
    auto* texture = form->get_graphics_context()->create_texture(material);

    auto cube = Render::Cube(Position3::null(), form->get_graphics_context());
    cube.set_texture(texture);

    auto paral = Render::Parallelepiped(Position3(-15, -7, -15), form->get_graphics_context(), Vector3(30, 1, 30));
	paral.set_texture(texture);

    PhysicsModule module;

    module.add_element(RigidBody(&cube.transform));
	
    form->get_graphics_context()->worldspace()->add_object(&cube);
    form->get_graphics_context()->worldspace()->add_object(&paral);
	
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
