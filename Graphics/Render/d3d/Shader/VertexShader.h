#pragma once
#include "Shader.h"

namespace Render {
	class VertexShader : public Shader
	{
		void construct(ID3DBlob* shader_blob) override;
		
		ID3D11VertexShader* _shader;
	public:

		void create_input_layout(const D3D11_INPUT_ELEMENT_DESC*elements,UINT num_elements,ID3D11InputLayout**layout);
		
		VertexShader(Core::GraphicsContext* engine);

		void bind() override;
	};
}
