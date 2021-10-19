#include "GEModuleLoader.h"
#include <Windows.h>
#include <vector>

std::vector<GeModule> g_modules;

GeModule* GELoadModule(wchar_t* path)
{
	const auto handle = LoadLibraryW(path);
	if(handle == nullptr)
	{
		return nullptr;
	}
	const auto module_main = (GEModuleMain)GetProcAddress(handle, "GEMain");
	if(module_main != nullptr)
	{
		GeModule ge_module;
		ge_module.path = path;
		ge_module.index = GEGetNewModuleIndex();
		ge_module.features = GE_MODULE_FEATURE_DX11 | GE_MODULE_FEATURE_WIN_OS;
		ge_module.unload_func = nullptr;
		if(module_main(&ge_module))
		{
			const auto last_element_index = g_modules.size();
			g_modules.push_back(ge_module);

			CloseHandle(handle);
			return &g_modules[last_element_index];
		}
	}

	CloseHandle(handle);
	return nullptr;
}

GEModuleIndex GEGetNewModuleIndex()
{
	return g_modules.size();
}

void GEUnloadModule(GeModule module)
{
	module.unload_func(&module);

}
