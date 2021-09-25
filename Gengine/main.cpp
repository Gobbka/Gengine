#include <iostream>
#include <Windows.h>
#include "Graphics.h"

#include "FreeImage.h"

#include <fstream>

#include "PhysicsModule.h"
#include "UIContext.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

#include <assimp/scene.h>
#include "Debugger/PipeServer.h"
#include "Render/d3d/Buffer/IndexBuffer.h"

#include <Ecs/Ecs.h>
#include <chrono>

#include <BinaryReader.h>
#include <Graphics/SpriteFont.h>
#include <Render/I3DObject/Parallelepiped/Parallelepiped.h>
#include <Render/Light/DirectionLightComponent.h>

#include "Graphics/Components/TextComponent.h"
#include "Loaders/AssetsLoader.h"
#include "Logger/Logger.h"
#include "Types/Material.h"

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
    AllocLoggerConsole();
    LogW(lpCmdLine);
	
    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    auto* context = form->get_graphics_context();

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
    	form->get_ui()->window_proc(msg, wp, lp);
    };

    auto stone_material = Render::Material();
    auto wood_material  = Render::Material();
    auto red_material = Render::Material(Color3::from_rgb(255, 50, 50));

    AssetsLoader::load_png(L"assets\\stone.png", stone_material);
    AssetsLoader::load_png(L"assets\\wood.png", wood_material);
	
    auto* stone_texture = context->get_device()->create_texture(stone_material);
    auto* wood_texture = context->get_device()->create_texture(wood_material);
    auto* red_texture = context->get_device()->create_texture(red_material);

    auto*light = form->editorScene->create_direction_light();
    auto component = light->get<Render::DirectionLightComponent>();
    component->set_position(Position3(-4.14113426f, 2.09657478f, -4.79795313f));
    component->set_rotation(Vector3(0.519999862f, 0.880000114f, 0));
	
    auto* cube = form->editorScene->create_model(red_texture);
    auto* platform = form->editorScene->create_model(stone_texture);
    platform->get<Render::MeshRenderer>()->transform.set_position(Position3{ 0,-7,0 });

    cube->get<Render::MeshRenderer>()->add_mesh(Render::Cube::make_independent(context, Position3::null(), 5));
	
    platform->get<Render::MeshRenderer>()->add_mesh(Render::Parallelepiped::make_independent(context, Position3::null(), Vector3{ 27,3,27 }));

    Render::SpriteFont font(context->get_device(), L"visby.spritefont");

    auto* text = form->main_scene->create_entity();
    auto text_comp = text->assign<Render::TextComponent>(context);
    text_comp->font = &font;
    text_comp->set_text(L"GEngine is the best engine");

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)debugger_loop, nullptr, 0, 0);

    form->main_scene->world()->registerSystem(new PhysicsModule());

    auto time = std::chrono::high_resolution_clock::now();

	while(true)
	{
        form->peek();
        form->update();
        form->force_draw();

        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - time);

        form->main_scene->world()->tick(1.f/(float)duration.count());
		
        time = now;
	}
}
