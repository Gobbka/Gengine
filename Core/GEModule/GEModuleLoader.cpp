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
	GeModule module;
	module.startup = (GEModule_Startup)GetProcAddress(handle, "GEModule_Startup");
	module.unload = (GEModule_Unload)GetProcAddress(handle, "GEModule_Unload");
	module.query = (GEModule_Query)GetProcAddress(handle, "GEModule_Query");
	module.index = GEGetNewModuleIndex();
	module.path = path;

	if (module.startup)
		module.startup();

	g_modules.push_back(module);
	CloseHandle(handle);
	return &g_modules[g_modules.size()];
}

GEModuleIndex GEGetNewModuleIndex()
{
	return g_modules.size();
}

void GEUnloadModule(GeModule module)
{
	if (module.unload)
		module.unload();
}
