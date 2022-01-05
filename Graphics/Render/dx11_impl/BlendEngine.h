#pragma once
#include <d3d11.h>
#include "../Common/GraphicsCommon.h"

namespace Render
{
	class DX11BlendEngine final
	{
		GEGraphics* _graphics;
		ID3D11BlendState* _blend;
	public:
		DX11BlendEngine(GEGraphics* graphics);
		
		void bind();
	};
}
