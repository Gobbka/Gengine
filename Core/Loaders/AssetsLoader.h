#pragma once
#include "../Types/Material.h"
#include "../BinaryReader.h"

class __declspec(dllexport) AssetsLoader
{
	static Render::Material materialFromPng(BYTE*ptr,UINT size);
public:
	static Render::Material loadImage(const wchar_t* path);
	static Render::Material loadPngResource(const wchar_t* name,const wchar_t*type);
	static BinaryReader makeSpriteFont(const wchar_t* font_name,UINT font_size);
};
