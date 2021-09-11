#include "AssetsLoader.h"

#include <FreeImage.h>
#include "../FS/FSFile.h"

void AssetsLoader::load_png(const wchar_t* path, Render::Material& material)
{
	auto file = FS::FSFile::read_file((wchar_t*)path);

	auto* fmemory = FreeImage_OpenMemory((BYTE*)file.data(), file.size());

	auto bitmap = FreeImage_LoadFromMemory(FIF_PNG, (FIMEMORY*)fmemory, ICO_MAKEALPHA);
	auto* nigger = FreeImage_GetBits(bitmap);

	material.load_bitmap(nigger, Surface((float)FreeImage_GetWidth(bitmap), (float)FreeImage_GetHeight(bitmap)));

	FreeImage_Unload(bitmap);
	FreeImage_CloseMemory(fmemory);

	material.reflect();
}
