#pragma once

#include "../../GraphicsBuildSettings.h"

#ifdef DRAW_LIBRARY_DX11
#include "../dx11_impl/BlendEngine.h"

namespace Render
{
	typedef DX11BlendEngine GEBlendEngine;
	
}

#endif
