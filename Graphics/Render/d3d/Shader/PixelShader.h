#pragma once
#include "Shader.h"

namespace Render {
	class PixelShader : public Shader
	{
		ID3D11PixelShader* _shader;
		void construct(ID3DBlob* shader_blob) override;
	public:
		ID3D11PixelShader* get_d3d11_ps() { return _shader; }
		
		PixelShader(Core::GraphicsContext* engine);
		PixelShader(Core::GraphicsContext* engine,const wchar_t*path);
	};
}
