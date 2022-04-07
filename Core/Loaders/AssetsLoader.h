#pragma once
#include "../Types/Material.h"
#include "../BinaryReader.h"

class __declspec(dllexport) AssetsLoader
{
	static Render::Material material_from_png(BYTE*ptr,UINT size);
public:
	static Render::Material load_png(const wchar_t* path);
	static Render::Material load_png_resource(const wchar_t* name,const wchar_t*type);
	static BinaryReader make_sprite_font(const wchar_t* font_name,UINT font_size);
};
