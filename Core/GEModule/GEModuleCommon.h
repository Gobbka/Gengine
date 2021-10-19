#pragma once

extern "C"{
	#define GEModuleCC __stdcall

	enum GEModuleFeatures : unsigned
	{
		GE_MODULE_FEATURE_DX11,
		GE_MODULE_FEATURE_WIN_OS,
	};

	
	typedef unsigned long long GEModuleIndex;

	typedef struct GeModule
	{
		unsigned(GEModuleCC* unload_func)(GeModule* lp_module);
		unsigned features;
		GEModuleIndex index;
		const wchar_t* path;
	} GeModule;

	typedef unsigned(GEModuleCC* GEModuleMain)(GeModule* lp_module);

	inline bool GEModuleRequireFeature(GeModule module, GEModuleFeatures feature)
	{
		return module.features & feature;
	}

	inline bool GEModuleRequireFeatures(GeModule module, unsigned features)
	{
		return module.features & features;
	}
}
