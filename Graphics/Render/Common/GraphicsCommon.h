#pragma once

#include "../../GraphicsBuildSettings.h"

#ifdef DRAW_LIBRARY_DX11
#include "../dx11_impl/BlendEngine.h"
#include "../dx11_impl/MaskEngine.h"

namespace Render
{
	typedef DX11BlendEngine GEBlendEngine;
	typedef DX11MaskEngine GEMaskEngine;
}

#endif
