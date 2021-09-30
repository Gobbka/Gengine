#include "AssetsLoader.h"

#include <FreeImage.h>
#include "../BinaryReader.h"
#include "../FS/FSFile.h"

Render::Material AssetsLoader::load_png(const wchar_t* path)
{
	BinaryReader reader(path);
	const auto size = reader.available();

	auto* fmemory = FreeImage_OpenMemory((BYTE*)reader.ReadArray<BYTE>(size), size);

	const auto  bitmap = FreeImage_LoadFromMemory(FIF_PNG, fmemory, ICO_MAKEALPHA);
	const auto* nigger = FreeImage_GetBits(bitmap);

	Render::Material material(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	material.reflect();

	return (Render::Material&&)material;
}
