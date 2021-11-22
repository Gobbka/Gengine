#include "AssetsLoader.h"

#include <FreeImage.h>
#include "../BinaryReader.h"
#include "../FS/FSFile.h"

Render::Material AssetsLoader::material_from_png(BYTE*ptr,UINT size)
{
	auto* fmemory = FreeImage_OpenMemory(ptr,size);

	const auto  bitmap = FreeImage_LoadFromMemory(FIF_PNG, fmemory, ICO_MAKEALPHA);
	const auto* nigger = FreeImage_GetBits(bitmap);

	Render::Material material(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	material.reflect();

	return (Render::Material&&)material;
}

Render::Material AssetsLoader::load_png(const wchar_t* path)
{
	BinaryReader reader(path);
	const auto size = reader.available();

	return material_from_png((BYTE*)reader.ReadArray<BYTE>(size), size);
}

Render::Material AssetsLoader::load_png_resource(const wchar_t* name,const wchar_t*type)
{
	const auto hmodule = GetModuleHandle(nullptr);
	const auto hResInfo = FindResource(nullptr, name, type);
	if(hResInfo)
	{
		const auto resource = LoadResource(hmodule, hResInfo);
		const auto res_size = SizeofResource(hmodule, hResInfo);

		const auto* lp_resource = LockResource(resource);

		auto* new_mem = new BYTE[res_size];

		memcpy(new_mem, lp_resource, res_size);

		return material_from_png(new_mem, res_size);
	}

	throw std::exception("Cannot find resource");
}
