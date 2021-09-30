#pragma once
#include "../Types/Material.h"

class __declspec(dllexport) AssetsLoader
{
public:
	static Render::Material load_png(const wchar_t* path);
};
