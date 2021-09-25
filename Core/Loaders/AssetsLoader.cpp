#include "AssetsLoader.h"

#include <FreeImage.h>
#include "../BinaryReader.h"
#include "../FS/FSFile.h"

void AssetsLoader::load_png(const wchar_t* path, Render::Material& material)
{
	BinaryReader reader(path);
	const auto size = reader.available();

	auto* fmemory = FreeImage_OpenMemory((BYTE*)reader.ReadArray<BYTE>(size), size);

	auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory, ICO_MAKEALPHA);
	auto* nigger = FreeImage_GetBits(bitmap);

	material.load_bitmap(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	material.reflect();
}
