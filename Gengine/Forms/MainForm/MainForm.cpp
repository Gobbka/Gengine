#include "MainForm.h"

#include <FreeImage.h>
#include <fstream>
#include <iostream>

#include "Graphics.h"
#include "elements/Panel/Panel.h"
#include "UIManager.h"
#include "InteractiveForm.h"
#include "Keyboard.h"
#include "../../../FSLib/FSDirectory.h"
#include "../../../FSLib/FSFile.h"
#include "Render/d3d/Buffer/Texture.h"

#include "Render/Engine/Camera.h"
#include "Render/I3DObject/Cube/Cube.h"

namespace UI
{
	class Directory : public Panel
	{
	private:
		FS::FSFile _directory;
	public:
		Directory(FS::FSFile directory, Position2 position, Surface resolution, Render::Texture* texture)
			: Panel(position, resolution, { 1.f,1.f,1.f,1.f }),
			_directory(directory)
		{
			//Panel::set_texture(texture);
			
		}

		void handle_db_click() override
		{
			system("start assets\\228.png");
			Parent::handle_db_click();
		}
	};
}

Render::Material* load_png(const wchar_t*path)
{
	auto file = FS::FSFile::read_file((wchar_t*)path);

	auto* fmemory = FreeImage_OpenMemory((BYTE*)file.data(), file.size());

	auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory);
	auto* nigger = FreeImage_GetBits(bitmap);

	auto* material = new Render::Material(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));
	// we need to swap it cuz driver returns BGR but we need RGB
	material->swap_channels(Render::Material::RGBChannel::red, Render::Material::RGBChannel::blue);

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	return material;
}

Forms::MainForm::MainForm(HINSTANCE hinst, UINT width, UINT height)
	: Form(hinst, width, height)
{
	auto* uicanvas = UI::UIManager::instance()->create_layer(get_graphics_context()->main_camera());

	_topbar_panel = new UI::Panel({ 0,0 }, { (float)width,30 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_worldspace_panel = new UI::Panel({ 0,-30 }, { 250,(float)height - 30.f }, { RGB_TO_FLOAT(20,20,20),1.f });
	
	_assets_panel_wrapper = new UI::Panel({ 250, -1 * (float)(height) + 250.f }, { (float)width-250,250 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_assets_panel_wrapper->add_element(
		new UI::Panel({ 0,0 }, { (float)width - 250,30 }, { RGB_TO_FLOAT(34,34,34),1.f })
	);

	_assets_panel = new UI::Panel({ 0,0}, { (float)width - 250,250-30 }, { RGB_TO_FLOAT(255,26,26),0.f });
	_assets_panel->styles.display = UI::ElementStyles::DisplayType::flex;

	_assets_panel_wrapper->add_element(_assets_panel);
	
	_folder_texture = get_graphics_context()->create_texture( load_png(L"assets\\folder.png"));
	_file_texture = get_graphics_context()->create_texture( load_png(L"assets\\file.png"));
	
	uicanvas
		->add_element(_topbar_panel)
		->add_element(_worldspace_panel)
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
		
		auto* panel = new UI::Directory(*(FS::FSFile*)file, { 0,0 }, { 120,120 }, lp_texture);
		
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

	if (Keyboard::pressed(VirtualKey::KEY_W)) // W
	{
		get_graphics_context()->main_camera()->adjust_position_relative(Position3(0.05f, 0, 0));
	}
	if (Keyboard::pressed(VirtualKey::KEY_S))
	{
		get_graphics_context()->main_camera()->adjust_position_relative(Position3(-0.05f, 0, 0));
	}
	if (Keyboard::pressed(VirtualKey::KEY_D))
	{
		get_graphics_context()->main_camera()->adjust_position_relative(Position3(0, 0, 0.05f));
	}
	if (Keyboard::pressed(VirtualKey::KEY_A))
	{
		get_graphics_context()->main_camera()->adjust_position_relative(Position3(0, 0, -0.05f));
	}
	if (Keyboard::pressed(VirtualKey::SPACE))
	{
		get_graphics_context()->main_camera()->adjust_position(Position3(0, 0.05f, 0));
	}
	if (Keyboard::pressed(VirtualKey::CONTROL))
	{
		get_graphics_context()->main_camera()->adjust_position(Position3(0, -0.05f, 0));
	}

	if (Keyboard::pressed(VirtualKey::LEFT))
	{
		get_graphics_context()->main_camera()->adjust_rotation((Vector3(0, -0.04f, 0)));
	}
	if (Keyboard::pressed(VirtualKey::RIGHT))
	{
		get_graphics_context()->main_camera()->adjust_rotation((Vector3(0, 0.04f, 0)));
	}
	if (Keyboard::pressed(VirtualKey::UP))
	{
		get_graphics_context()->main_camera()->adjust_rotation((Vector3(-0.04f, 0, 0)));
	}
	if (Keyboard::pressed(VirtualKey::DOWN))
	{
		get_graphics_context()->main_camera()->adjust_rotation((Vector3(0.04f, 0, 0)));
	}
}
