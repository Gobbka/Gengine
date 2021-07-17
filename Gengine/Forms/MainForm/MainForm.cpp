#include "MainForm.h"

#include <FreeImage.h>
#include <fstream>


#include "Graphics.h"
#include "elements/Panel/Panel.h"
#include "UIManager.h"
#include "InteractiveForm.h"
#include "Render/d3d/Buffer/Texture.h"

Render::Material* load_png(const wchar_t*path)
{
	std::ifstream ifs(path, std::ios::in | std::ios::binary | std::ifstream::ate);

	assert(ifs.is_open());

	auto size = (size_t)ifs.tellg();
	ifs.seekg(0);

	auto* ptr = new char[size];
	ifs.read(ptr, size);

	auto* fmemory = FreeImage_OpenMemory((BYTE*)ptr, size);
	auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory);

	auto* nigger = FreeImage_GetBits(bitmap);

	auto* material = new Render::Material(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));
	// we need to swap it cuz driver returns BGR but we need RGB
	material->swap_channels(Render::Material::RGBChannel::red, Render::Material::RGBChannel::blue);

	FreeImage_CloseMemory(fmemory);

	delete[] ptr;
	return material;
}

Forms::MainForm::MainForm(HINSTANCE hinst, UINT width, UINT height)
	: Form(hinst, width, height)
{
	auto* uicanvas = UI::UIManager::instance()->create_layer(get_graphics_context()->main_camera());

	_topbar_panel = new UI::Panel({ 0,0 }, { (float)width,30 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_worldspace_panel = new UI::Panel({ 0,-30 }, { 250,(float)height - 30.f }, { RGB_TO_FLOAT(20,20,20),1.f });
	
	_assets_panel = new UI::Panel({ 250, -1 * (float)(height) + 250.f }, { (float)width-250,250 }, { RGB_TO_FLOAT(26,26,26),1.f });
	_assets_panel->add_element(
		new UI::Panel({ 0,0 }, { (float)width - 250,30 }, { RGB_TO_FLOAT(34,34,34),1.f })
	);

	_folder_texture = get_graphics_context()->create_texture( load_png(L"folder.png"));

	
	uicanvas
		->add_element(_topbar_panel)
		->add_element(_worldspace_panel)
		->add_element(_assets_panel)
	;

}

void Forms::MainForm::handle_resize(Surface rect)
{
	auto width = rect.width;
	auto height = rect.height;
	
	_topbar_panel->set_resolution(Surface(width, 30));
	_worldspace_panel->set_resolution(Surface(250, height - 30));
	
	Form::handle_resize(rect);
}
