#include "MainForm.h"

#include <FreeImage.h>
#include <fstream>
#include <iostream>

#include <Window/Keyboard.h>
#include <FS/FSObject.h>
#include <FS/FSDirectory.h>

#include <Graphics.h>
#include <Render/d3d/Buffer/Texture.h>
#include <Render/Engine/Camera.h>
#include <elements/Panel/Panel.h>
#include <InteractiveForm.h>
#include <UIContext.h>

#include "Render/Light/DirectionLightComponent.h"
#include <Types/Material.h>

#include "Loaders/AssetsLoader.h"
#include <Animation/Animator.h>

#include "Elements/Panel/FlexColumnPanel.h"
#include "Elements/Panel/FlexRowPanel.h"
#include "Render/Engine/RenderTarget.h"

namespace UI
{
	class Directory : public Panel
	{
	private:
		FS::FSObject _object;
	public:
		Directory(FS::FSObject object, Position2 position, Surface resolution, Render::Texture* texture)
			: Panel(position, resolution, nullptr),
			_object(object)
		{
			Panel::set_texture(texture);
			
		}

		void handle_db_click() override
		{
			if(!_object.is_directory())
			{
				std::wstring command(L"start ");
				command += _object.path();
				
				_wsystem(command.c_str());
			}
		}

		void handle_mouse_enter() override
		{
			SetCursor(LoadCursor(0, IDC_HAND));
			Panel::handle_mouse_enter();
		}

		void handle_mouse_leave() override
		{
			SetCursor(LoadCursor(0, IDC_ARROW));
			Panel::handle_mouse_leave();
		}
		
		
	};
}

Forms::MainForm::MainForm(HINSTANCE hinst, UINT width, UINT height)
	: Form(hinst, width, height)
{
	main_scene->register_system(new UI::HandleAnimationSystem());
	auto main_cam = main_scene->get_main_camera()->get<Render::Camera>();
	main_cam->get_target_view()->clear_color = Color3XM(.1f, .1f, .1f);

	auto* uicanvas_entity = get_ui()->create_layer();
	
	_topbar_panel = new UI::Panel({ 0,0 }, { (float)width,30 }, { RGB_TO_FLOAT(26,26,26) });
	_worldspace_panel = new UI::Panel({ 0,-30 }, { 250,(float)height - 30.f }, { RGB_TO_FLOAT(20,20,20) });
	
	_assets_panel_wrapper = new UI::FlexColumnPanel ({ 250, -1 * (float)(height)+250.f }, { (float)width - 250,250 }, { RGB_TO_FLOAT(26,26,26) });
	_assets_panel_wrapper->add_element(
		new UI::Panel({ 0,0 }, { (float)width - 250,30 }, { RGB_TO_FLOAT(34,34,34) })
	);

	_render_panel = new UI::Panel({ 250, -30 }, { 840,468 }, nullptr);

	_assets_panel = new UI::FlexRowPanel({ 0,0}, { (float)width - 250,250-30 }, { RGB_TO_FLOAT(26,26,26) });
	_assets_panel->styles.display = UI::ElementStyles::DisplayType::flex;

	_assets_panel_wrapper->add_element(_assets_panel);

	auto folder_material = AssetsLoader::load_png(L"assets\\folder.png");
	auto file_material = AssetsLoader::load_png(L"assets\\file.png");

	_folder_texture = get_graphics_context()->get_device()->create_texture(folder_material);
	_file_texture = get_graphics_context()->get_device()->create_texture(file_material);

	editorScene = get_graphics_context()->create_scene();
	auto worldTexture = new Render::RenderTarget(get_graphics_context(),{1400,780});
	auto* editorCam = editorScene->create_camera(worldTexture);
	editorScene->set_main_camera(editorCam);
	auto cam = editorCam->get<Render::Camera>();
	cam->get_target_view()->clear_color.a = 0.f;

	_render_panel->set_texture(worldTexture->get_texture());

	auto uicanvas = uicanvas_entity->get<UI::InteractiveForm>();
	
	uicanvas
		->add_element(_topbar_panel)
		->add_element(_worldspace_panel)
		->add_element(_render_panel)
	
		->add_element(_assets_panel_wrapper)
	;
	
	scan_assets_directory();
}

void Forms::MainForm::scan_assets_directory()
{
	FS::FSDirectory directory((wchar_t*)L"assets");

	directory.foreach([&](FS::FSObject* file)
	{
		Render::Texture* lp_texture = file->is_directory() ? _folder_texture : _file_texture;
		
		auto* panel = new UI::Directory(*file, { 0,0 }, { 120,120 }, lp_texture);
		
		_assets_panel->add_element(panel);
	});

}

void Forms::MainForm::handle_resize(Surface rect)
{
	auto width = rect.width;
	auto height = rect.height;
	
	_topbar_panel->set_resolution(Surface(width, 30));
	_worldspace_panel->set_resolution(Surface(250, height - 30));
	
	Form::handle_resize(rect);
}

void Forms::MainForm::update()
{
	static float scale = 45.f;
	auto camera = editorScene->get_main_camera()->get<Render::Camera>();
	
	if (keyboard->pressed(VirtualKey::KEY_W)) // W
	{
		camera->adjust_position_relative(Position3(0.05f, 0, 0));
	}
	if (keyboard->pressed(VirtualKey::KEY_S))
	{
		camera->adjust_position_relative(Position3(-0.05f, 0, 0));
	}
	if (keyboard->pressed(VirtualKey::KEY_D))
	{
		camera->adjust_position_relative(Position3(0, 0, 0.05f));
	}
	if (keyboard->pressed(VirtualKey::KEY_A))
	{
		camera->adjust_position_relative(Position3(0, 0, -0.05f));
	}
	if (keyboard->pressed(VirtualKey::SPACE))
	{
		camera->set_fov(scale);
		scale += 0.1f;
	}
	if (keyboard->pressed(VirtualKey::CONTROL))
	{
		camera->set_fov(scale);
		scale -= 0.1f;
	}
	if (keyboard->pressed(VirtualKey::LEFT))
	{
		camera->adjust_rotation((Vector3(0, -0.04f, 0)));
	}
	if (keyboard->pressed(VirtualKey::RIGHT))
	{
		camera->adjust_rotation((Vector3(0, 0.04f, 0)));
	}
	if (keyboard->pressed(VirtualKey::UP))
	{
		camera->adjust_rotation((Vector3(-0.04f, 0, 0)));
	}
	if (keyboard->pressed(VirtualKey::DOWN))
	{
		camera->adjust_rotation((Vector3(0.04f, 0, 0)));
	}
}
