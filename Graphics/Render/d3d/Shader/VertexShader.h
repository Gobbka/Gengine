#pragma once
#include "IShader.h"
#include <d3d11.h>

namespace Render {
	class __declspec(dllexport) VertexShader : public IShader
	{
		void construct(ID3DBlob* shader_blob);
		void link(ID3DBlob* blob,const D3D11_INPUT_ELEMENT_DESC* layout,UINT num_elements);

		ID3D11VertexShader* _shader;
		ID3D11InputLayout* _layout;
	public:

		ID3D11VertexShader* get_d11_vs();
		ID3D11InputLayout* get_d11_il();
		
		VertexShader(Core::GraphicsContext* engine,const char*data,size_t size,const D3D11_INPUT_ELEMENT_DESC*layout,UINT num_elements);
		VertexShader(Core::GraphicsContext* ctx, const wchar_t* file_name,const D3D11_INPUT_ELEMENT_DESC* layout, UINT num_elements);

		void bind();
	};
}
