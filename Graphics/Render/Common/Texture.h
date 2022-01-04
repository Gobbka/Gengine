#pragma once

#include "../../GraphicsBuildSettings.h"

#ifdef DRAW_LIBRARY_DX11
#include "../dx11_impl/Texture.h"

namespace Render
{
	typedef DX11Texture GETexture;
}
#endif