#include "Graphics.h"

#include "PhysicsModule.h"
#include "UIContext.h"
#include "Forms/MainForm/MainForm.h"
#include "Forms/WelcomeForm/WelcomeForm.h"
#include <Graphics/I3DObject/Cube/Cube.h>
#include <Graphics/I3DObject/Parallelepiped/Parallelepiped.h>
#include "Debugger/PipeServer.h"
#include <Ecs/Ecs.h>
#include <chrono>

#include <Graphics/Components/DirectionLightComponent.h>
#include <Graphics/Components/MeshRenderer.h>
#include <Graphics/Components/LightViewer.h>
#include <Graphics/Components/PointLightComponent.h>
#include <Graphics/Components/SkyboxComponent.h>
#include <Loaders/AssetsLoader.h>
#include <Logger/Logger.h>
#include <Graphics/Camera.h>
#include <Types/Material.h>
#include <XML/XMLDecoder.h>

#include "Input/Console.h"
#include "Window/WindowsManager.h"

void debugger_loop()
{
	// const auto* server = PipeServer::create(LR"(\\.\pipe\GENGINE_DBG)");

	//while(true)
	//{
 //       char* buffer;
 //       server->receive(&buffer);

 //       std::cout << "[DBG]" << buffer << '\n';
	//}
}

int WINAPI wWinMain(
    _In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR lpCmdLine,
    _In_ int nShowCmd
)
{
    GEConsole::show();
    LogW(lpCmdLine);

    auto*form = new Forms::MainForm(hInstance, 1400, 780);
    form->show();

    auto* context = form->get_graphics_context();

    form->on_wndproc = [&](UINT msg, WPARAM wp, LPARAM lp)
    {
    	form->get_ui()->windowProc(msg, wp, lp);
    };

    auto* stone_texture = context->get_device()->create_texture(AssetsLoader::loadImage(L"assets\\Pebbles_027_BaseColor.png"));
    auto* stone_texture_normals = context->get_device()->create_texture(AssetsLoader::loadImage(L"assets\\Pebbles_027_Normal.png"));
    auto* workbench_texture = context->get_device()->create_texture(AssetsLoader::loadImage(L"assets\\workspace_background.png"));
    auto* red_texture = context->get_device()->create_texture(Render::Material(Color3XM::from_rgb(255,50,50)));

    auto*light = form->editorScene->create_direction_light();
    const auto component = light->get<Render::DirectionLightComponent>();
    component->set_position(Position3(-4.14113426f, 2.09657478f, -4.79795313f));
    component->set_rotation(Vector3(0.519999862f, 0.880000114f, 0));

    form->editorScene->create_point_light({ 1,{1,1,1},{-3,3,10} });
    form->editorScene->getMainCamera()->assign<Render::SkyboxComponent>(workbench_texture);
    auto* cube = form->editorScene->createModel(stone_texture,stone_texture_normals);
    auto* platform = form->editorScene->createModel(red_texture);
    platform->get<Render::MeshRenderer>()->transform.set_position(Position3{ 0,-7,0 });

    cube->get<Render::MeshRenderer>()->add_mesh(Render::Cube::make_independent(context, Position3::null(), 5));
    platform->get<Render::MeshRenderer>()->add_mesh(Render::Parallelepiped::make_independent(context, Position3::null(), Vector3{ 27,3,27 }));

    form->editorScene->getMainCamera()
		->assign<Render::LightViewer>(
            context,
            form->main_scene->getMainCamera()->get<Render::Camera>()->get_view_resolution()
	);

    form->main_scene->world()->registerSystem(new PhysicsModule());

    auto time = std::chrono::high_resolution_clock::now();

	auto& windows = *GE::WindowsManager::instance();

	while(windows.hasLiveWindows())
	{
        for(auto* window : windows)
        {
            if(window->peek())
            {
                ((GE::Form*)window)->update();
                ((GE::Form*)window)->force_draw();
            }else
            {
                delete window;
                break;
            }
        }

        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - time);

        for (auto* window : windows)
        {
            ((GE::Form*)window)->main_scene->world()->tick(1.f / (float)duration.count());
        }

        time = now;
	}
}
