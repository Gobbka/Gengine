#pragma once
#include "GEModuleCommon.h"

extern "C" {
	GeModule* GELoadModule(const wchar_t*path);
	GEModuleIndex GEGetNewModuleIndex();
	void GEUnloadModule(GeModule module);
}
