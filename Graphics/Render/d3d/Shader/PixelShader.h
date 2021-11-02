#pragma once
#include <d3d11.h>

#include "IShader.h"

namespace Render {
	class PixelShader : public IShader
	{
		ID3D11PixelShader* _shader;
		void construct(ID3DBlob* shader_blob);
	public:
		ID3D11PixelShader* get_d3d11_ps() { return _shader; }

		PixelShader(Core::GraphicsContext* engine,const wchar_t*path);
	};
}
