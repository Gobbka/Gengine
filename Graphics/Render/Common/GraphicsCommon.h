#pragma once
#include "../../GraphicsBuildSettings.h"

#ifdef DRAW_LIBRARY_DX11
#include <DirectXMath.h>

namespace Render
{
	class DX11Texture;
	class DX11MaskEngine;
	class DX11BlendEngine;
	class DX11Rasterizer;
	class DX11IndexBuffer;
	class DX11RenderTarget;
	class DX11SamplerState;
	class DX11DepthStencil;
	class DX11Graphics;
	class DX11ConstantBuffer;
	class DX11VBuffer;
	template<typename T>
	class ConstantBuffer;

	typedef DX11Texture GETexture;
	typedef DX11MaskEngine GEMaskEngine;
	typedef DX11BlendEngine GEBlendEngine;
	typedef DX11Rasterizer GERasterizer;
	typedef DX11IndexBuffer GEIndexBuffer;
	typedef DX11RenderTarget GERenderTarget;
	typedef DX11SamplerState GESamplerState;
	typedef DX11DepthStencil GEDepthStencil;
	typedef DX11Graphics GEGraphics;
	typedef DX11ConstantBuffer GEConstantBuffer;
	typedef DX11VBuffer GEVBuffer_Impl;

	typedef DirectX::XMMATRIX GEMatrix;
}

#endif
