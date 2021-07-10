#pragma once
#include "Shader.h"

namespace Render {
	class PixelShader : public Shader
	{
		ID3D11PixelShader* _shader;
		void construct(ID3DBlob* shader_blob) override;
	public:
		PixelShader(D3DEngine* engine);

		void bind() override;
	};
}
