#include <iostream>
#include <Windows.h>
#include "Graphics.h"
#include "WindowsManager.h"

#include "FreeImage.h"
#include "Render/d3d/Buffer/Texture.h"

#include <fstream>

#include "PhysicsModule.h"
#include "UIManager.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

#include <assimp/importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/mesh.h>

#include "Debugger/PipeServer.h"
#include "Render/d3d/Buffer/IndexBuffer.h"
#include "Render/d3d/Buffer/VertexBuffer.h"

#include <Ecs/Ecs.h>
#include <chrono>

Render::Model* load_model(const wchar_t*path,Core::GraphicsContext*context)
{
    Assimp::Importer importer;
    auto* scene = importer.ReadFile("assets\\gun.obj", aiProcess_Triangulate | aiProcess_ConvertToLeftHanded);
	
    assert(scene != nullptr);

    for (UINT i = 0; i < scene->mRootNode->mNumMeshes; i++)
    {
        auto* mesh = scene->mMeshes[scene->mRootNode->mMeshes[i]];
        auto* vert = context->buffer_allocator()->alloc_vertex_buffer(context,mesh->mNumVertices);
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
        UI::UIManager::instance()->window_proc(msg, wp, lp);
    };

    auto* material = load_png(L"assets\\mine4ok.png");
    auto* negr = load_png(L"assets\\workspace_background.png");

    auto* texture = form->get_graphics_context()->create_texture(material);

    auto* world = ECS::World::createWorld();
    auto* ent = world->create();
    auto ch = ent->assign<Render::Model>();
	
    auto cube = Render::Model();
    auto cube_mesh = Render::Cube(Position3::null(), form->get_graphics_context());
    auto nigga_mesh = Render::Parallelepiped(Position3(15,15,0), form->get_graphics_context(),Vector3{9,3,9});
    cube_mesh.set_texture(texture);

    cube.add_mesh(&cube_mesh);
    cube.add_mesh(&nigga_mesh);

    auto paral = Render::Parallelepiped(Position3(-15, -7, -15), form->get_graphics_context(), Vector3(30, 1, 30));
	paral.set_texture(texture);
	
    PhysicsModule module;
	
    form->get_graphics_context()->worldspace()->add_object(&cube);
    //form->get_graphics_context()->worldspace()->add_object(&paral);

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)debugger_loop, nullptr, 0, 0);
	
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
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(now - time);
		
        world->tick((float)duration.count());

        time = now;
	}
}
