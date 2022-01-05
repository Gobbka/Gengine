#pragma once

extern "C"{
	#define GEModuleCC __stdcall
	
	typedef unsigned long long GEModuleIndex;
	typedef unsigned GE_STATUS;
	typedef GE_STATUS(GEModuleCC* GEModule_Startup)();
	typedef GE_STATUS(GEModuleCC* GEModule_Unload)();
	typedef GE_STATUS(GEModuleCC* GEModule_Query)(unsigned query_type, void* data);

	typedef struct GeModule
	{
		GEModule_Startup startup;
		GEModule_Unload unload;
		GEModule_Query query;
		GEModuleIndex index;
		const wchar_t* path;
	} GeModule;
}
