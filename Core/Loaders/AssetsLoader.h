#pragma once
#include "../Types/Material.h"
class __declspec(dllexport) AssetsLoader
{
public:
	static void load_png(const wchar_t* path, Render::Material& material);
};
