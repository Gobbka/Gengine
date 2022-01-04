#pragma once
#include "../../GraphicsBuildSettings.h"

#ifdef DRAW_LIBRARY_DX11

namespace Render
{
	class DX11Texture;
	class DX11MaskEngine;
	class DX11BlendEngine;
	class DX11Rasterizer;

	typedef DX11Texture GETexture;
	typedef DX11MaskEngine GEMaskEngine;
	typedef DX11BlendEngine GEBlendEngine;
	typedef DX11Rasterizer GERasterizer;
}

#endif
