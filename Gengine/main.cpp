#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"

#include "FreeImage.h"
#include "Render/d3d/Buffer/Texture.h"

#include <fstream>

#include "PhysicsModule.h"
#include "UIContext.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

#include <assimp/importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include "Debugger/PipeServer.h"
#include "Render/d3d/Buffer/IndexBuffer.h"

#include <Ecs/Ecs.h>
#include <chrono>

#include "Graphics/Components/ColorComponent.h"
#include "Graphics/Components/TextureComponent.h"
#include "Render/I3DObject/Parallelepiped/Parallelepiped.h"

Render::MeshContainerComponent* load_model(const wchar_t*path,Core::GraphicsContext*context)
{
    Assimp::Importer importer;
    auto* scene = importer.ReadFile("assets\\gun.obj", aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	
    assert(scene != nullptr);

    for (UINT i = 0; i < scene->mRootNode->mNumMeshes; i++)
    {
        auto* mesh = scene->mMeshes[scene->mRootNode->mMeshes[i]];
        auto* vert = context->get_device()->alloc_vertex_buffer(context,mesh->mNumVertices);
    }

    return nullptr;
}

extern Render::Material* load_png(const wchar_t* path);

void debugger_loop()
{
    auto* server = PipeServer::create(L"\\\\.\\pipe\\GENGINE_DBG");

	while(true)
	{
        char* buffer;
        server->receive(&buffer);

        std::cout << "[DBG]" << buffer << '\n';
	}
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

    std::wcout << lpCmdLine<<'\n';
	
    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
    	form->get_ui()->window_proc(msg, wp, lp);
    };

    auto* material = load_png(L"assets\\stone.png");
    auto* negr = load_png(L"assets\\wood.png");

    auto* graphics = form->get_graphics_context();
	
    auto* texture = form->get_graphics_context()->get_device()->create_texture(material);
    auto* negr_texture = form->get_graphics_context()->get_device()->create_texture(negr);

    auto* device = graphics->get_device();
	
    auto* cube = device->create_model();
    auto* platform = device->create_model();
    platform->get<Render::MeshContainerComponent>()->transform.set_position(Position3{ 0,-7,0 });

    cube->get<Render::MeshContainerComponent>()->add_mesh(Render::Cube::make(form->get_graphics_context(), Position3::null(), 5));
    cube->assign<Render::TextureComponent>(negr_texture);
	
    platform->get<Render::MeshContainerComponent>()->add_mesh(Render::Parallelepiped::make(form->get_graphics_context(), Position3::null(), Vector3{ 9,3,9 }));
    platform->assign<Render::TextureComponent>(texture);

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)debugger_loop, nullptr, 0, 0);

    graphics->worldspace()->registerSystem(new PhysicsModule());
	
    MSG msg;

    auto time = std::chrono::high_resolution_clock::now();
	
	while(true)
	{
		
		if(PeekMessage(&msg, nullptr,0, 0, PM_REMOVE))
		{
            TranslateMessage(&msg);
            DispatchMessage(&msg);
		}

        form->update();
        form->force_draw();

        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - time);

        graphics->worldspace()->tick(1.f/duration.count());
		
        time = now;
	}
}
