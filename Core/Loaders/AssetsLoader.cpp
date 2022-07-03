#include "AssetsLoader.h"

#include <FreeImage.h>
#include "../BinaryReader.h"
#include "../FS/FSFile.h"
#include "../GEString.h"
#include <sstream>
#include <ostream>

Render::Material AssetsLoader::materialFromPng(BYTE*ptr,UINT size)
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

Render::Material AssetsLoader::loadImage(const wchar_t* path)
{
	const GEString path_str(path);

	BinaryReader reader(path);
	const auto size = reader.available();

	if(path_str.endsWith(L".png"))
	{
		return materialFromPng((BYTE*)reader.ReadArray<BYTE>(size), size);
	}

	throw std::exception("Unknown image format");
}

Render::Material AssetsLoader::loadPngResource(const wchar_t* name,const wchar_t*type)
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

		return materialFromPng(new_mem, res_size);
	}

	throw std::exception("Cannot find resource");
}

BinaryReader AssetsLoader::makeSpriteFont(const wchar_t* font_name,UINT font_size)
{
	STARTUPINFO info{ sizeof(info) };
	PROCESS_INFORMATION process_info;
	
	std::wostringstream out_file_name_s;
	out_file_name_s << font_name << "_" << font_size << L"px.tempfont";

	std::wostringstream ofs;
	ofs << L"cmd \"" << font_name << "\" \"" << out_file_name_s.str() << "\" /FontSize:"<<font_size;

	const auto command = ofs.str();

	if (
		CreateProcess(
			L"MakeSpriteFont.exe",
			(LPWSTR)command.c_str(),
			nullptr, 
			nullptr, 
			true, 
			0, 
			nullptr, 
			nullptr,
			&info, 
			&process_info)
		)
	{
		WaitForSingleObject(process_info.hProcess, INFINITE);
		CloseHandle(process_info.hProcess);
		CloseHandle(process_info.hThread);
	}

	auto file_name = out_file_name_s.str();
	BinaryReader reader(file_name.c_str());

	FS::File file(GEString(file_name.c_str()), 0, (char*)nullptr);
	file.remove();

	return std::move(reader);
}
