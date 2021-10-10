#ifdef _MSC_VER
#include <CodeAnalysis/Warnings.h>
#pragma  warning(push)
#pragma warning(disable : ALL_CODE_ANALYSIS_WARNINGS)
#endif
#include <python/Python.h>
#include <pybind11/embed.h>
#ifdef _MSC_VER
#pragma warning(pop)
#endif


#include <iostream>
#include <Windows.h>
#include "Graphics.h"

#include "FreeImage.h"
#include "PhysicsModule.h"
#include "UIContext.h"
#include "Forms/MainForm/MainForm.h"
#include "Render/I3DObject/Cube/Cube.h"
#include "Debugger/PipeServer.h"
#include "Render/d3d/Buffer/IndexBuffer.h"

#include <Ecs/Ecs.h>
#include <chrono>

#include <BinaryReader.h>
#include <Graphics/SpriteFont.h>
#include <Render/I3DObject/Parallelepiped/Parallelepiped.h>
#include <Render/Light/DirectionLightComponent.h>

#include "Graphics/Components/MeshRenderer.h"
#include "Graphics/Components/NormalsRenderTarget.h"
#include "Graphics/Components/TextComponent.h"
#include "Loaders/AssetsLoader.h"
#include "Logger/Logger.h"
#include "Render/Engine/Camera.h"
#include "Types/Material.h"

void debugger_loop()
{
	const auto* server = PipeServer::create(L"\\\\.\\pipe\\GENGINE_DBG");

	while(true)
	{
        char* buffer;
        server->receive(&buffer);

        std::cout << "[DBG]" << buffer << '\n';
	}
}

void some_fn(char*str)
{
    LogA("[NIGGA]: " << str);
}

PYBIND11_EMBEDDED_MODULE(nigga,handle)
{
    handle.doc() = "This is nigger";
    
    handle.def("say", &some_fn);
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

    BinaryReader reader(L"python\\test.py");
    auto* script = reader.to_string();
    pybind11::scoped_interpreter guard{};
    pybind11::exec(script);
    delete[] script;

    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();
    form->background = { 17,17,17 };

    auto* context = form->get_graphics_context();

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
    	form->get_ui()->window_proc(msg, wp, lp);
    };

    auto stone_material = AssetsLoader::load_png(L"assets\\stone.png");
    Render::Material red_material(Color3XM::from_rgb(255, 50, 50));
	
    auto* stone_texture = context->get_device()->create_texture(stone_material);
    auto* red_texture = context->get_device()->create_texture(red_material);

    auto*light = form->editorScene->create_direction_light();
    const auto component = light->get<Render::DirectionLightComponent>();
    component->set_position(Position3(-4.14113426f, 2.09657478f, -4.79795313f));
    component->set_rotation(Vector3(0.519999862f, 0.880000114f, 0));
	
    auto* cube = form->editorScene->create_model(red_texture);
    auto* platform = form->editorScene->create_model(stone_texture);
    platform->get<Render::MeshRenderer>()->transform.set_position(Position3{ 0,-7,0 });

    cube->get<Render::MeshRenderer>()->add_mesh(Render::Cube::make_independent(context, Position3::null(), 5));
    platform->get<Render::MeshRenderer>()->add_mesh(Render::Parallelepiped::make_independent(context, Position3::null(), Vector3{ 27,3,27 }));

    Render::SpriteFont font(context->get_device(), L"visby.spritefont");

    form->main_scene->get_main_camera()
		->assign<Render::NormalsRenderTarget>(
            context,
            form->main_scene->get_main_camera()->get<Render::Camera>()->get_view_resolution()
	);
    
    auto* text = form->main_scene->create_entity();
    auto text_comp = text->assign<Render::TextComponent>(context,&font);
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
