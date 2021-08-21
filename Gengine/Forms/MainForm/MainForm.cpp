#include "MainForm.h"

#include <FreeImage.h>
#include <fstream>
#include <iostream>

#include <Keyboard.h>
#include <FS/FSFile.h>
#include <FS/FSObject.h>
#include <FS/FSDirectory.h>

#include <Graphics.h>
#include <Render/d3d/Buffer/Texture.h>
#include <Render/Engine/Camera.h>
#include <elements/Panel/Panel.h>
#include <InteractiveForm.h>
#include <UIManager.h>

#include "Render/Light/DirectionLight.h"


namespace UI
{
	class Directory : public Panel
	{
	private:
		FS::FSObject _object;
	public:
		Directory(FS::FSObject object, Position2 position, Surface resolution, Render::Texture* texture)
			: Panel(position, resolution, { 1.f,1.f,1.f,1.f }),
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
			Parent::handle_db_click();
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

Render::Material* load_png(const wchar_t*path)
{
	auto file = FS::FSFile::read_file((wchar_t*)path);

	auto* fmemory = FreeImage_OpenMemory((BYTE*)file.data(), file.size());

	auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory, ICO_MAKEALPHA);
	auto* nigger = FreeImage_GetBits(bitmap);
	
	auto gabka = FreeImage_GetColorType(bitmap);

	auto* material = 
		new Render::Material(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));
	// we need to swap it cuz driver returns BGR but we need RGB
	//material->swap_channels(Render::Material::RGBChannel::red, Render::Material::RGBChannel::blue);

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	return material;
}

Forms::MainForm::MainForm(HINSTANCE hinst, UINT width, UINT height)
	: Form(hinst, width, height)
{
	auto main_cam = main_camera->get<Render::Camera>();
	auto* options = main_cam->options();
	options->render_2d = true;
	options->render_3d = false;
	
	auto* uicanvas = UI::UIManager::instance()->create_layer(main_cam.get_ptr());

	_topbar_panel = new UI::Panel({ 0,0 }, { (float)width,30 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_worldspace_panel = new UI::Panel({ 0,-30 }, { 250,(float)height - 30.f }, { RGB_TO_FLOAT(20,20,20),1.f });
	
	_assets_panel_wrapper = new UI::Panel({ 250, -1 * (float)(height) + 250.f }, { (float)width-250,250 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_assets_panel_wrapper->add_element(
		new UI::Panel({ 0,0 }, { (float)width - 250,30 }, { RGB_TO_FLOAT(34,34,34),1.f })
	);

	_render_panel = new UI::Panel({ 250, -30 }, { 840,468 }, { RGB_TO_FLOAT(255,0,0),1.f });

	_assets_panel = new UI::Panel({ 0,0}, { (float)width - 250,250-30 }, { RGB_TO_FLOAT(255,26,26),0.f });
	_assets_panel->styles.display = UI::ElementStyles::DisplayType::flex;

	_assets_panel_wrapper->add_element(_assets_panel);
	
	_folder_texture = get_graphics_context()->create_texture( load_png(L"assets\\folder.png"));
	_file_texture = get_graphics_context()->create_texture(load_png(L"assets\\file.png"));

	auto worldTexture = new Render::RenderTarget(get_graphics_context(),{1400,780});
	_worldCamera = get_graphics_context()->create_camera(worldTexture);
	auto cam = _worldCamera->get<Render::Camera>();
	auto* cam_options = cam->options();
	cam_options->render_2d = false;
	cam_options->render_3d = true;
	cam->set_light(new Render::DirectionLight(get_graphics_context()));

	_render_panel->set_texture(worldTexture->get_texture());

	_worldspace_panel->unique_id = 228;
	
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
	static float scale = 90.f;
	auto camera = _worldCamera->get<Render::Camera>();
	
	if (Keyboard::pressed(VirtualKey::KEY_W)) // W
	{
		camera->adjust_position_relative(Position3(0.05f, 0, 0));
	}
	if (Keyboard::pressed(VirtualKey::KEY_S))
	{
		camera->adjust_position_relative(Position3(-0.05f, 0, 0));
	}
	if (Keyboard::pressed(VirtualKey::KEY_D))
	{
		camera->adjust_position_relative(Position3(0, 0, 0.05f));
	}
	if (Keyboard::pressed(VirtualKey::KEY_A))
	{
		camera->adjust_position_relative(Position3(0, 0, -0.05f));
	}
	if (Keyboard::pressed(VirtualKey::SPACE))
	{
		camera->set_fov(scale);
		scale += 0.1f;
	}
	if (Keyboard::pressed(VirtualKey::CONTROL))
	{
		camera->set_fov(scale);
		scale -= 0.1f;
	}

	if (Keyboard::pressed(VirtualKey::LEFT))
	{
		camera->adjust_rotation((Vector3(0, -0.04f, 0)));
	}
	if (Keyboard::pressed(VirtualKey::RIGHT))
	{
		camera->adjust_rotation((Vector3(0, 0.04f, 0)));
	}
	if (Keyboard::pressed(VirtualKey::UP))
	{
		camera->adjust_rotation((Vector3(-0.04f, 0, 0)));
	}
	if (Keyboard::pressed(VirtualKey::DOWN))
	{
		camera->adjust_rotation((Vector3(0.04f, 0, 0)));
	}
}
