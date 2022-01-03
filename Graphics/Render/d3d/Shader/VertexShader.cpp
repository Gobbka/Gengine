#include "VertexShader.h"

#include <d3dcompiler.h>
#include "../../../IGContext.h"
#include "../../../Graphics.h"

void Render::VertexShader::construct(ID3DBlob* shader_blob)
{
	context->device->CreateVertexShader(
		shader_blob->GetBufferPointer(),
		shader_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

void Render::VertexShader::link(ID3DBlob* blob,const D3D11_INPUT_ELEMENT_DESC* layout,UINT num_elements)
{
	GEAssert(context->device->CreateInputLayout(
		layout,
		num_elements,
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		&_layout
	)).abort(TEXT("VertexShader.cpp: cannot link  input layout with elements description"));
}

ID3D11VertexShader* Render::VertexShader::get_d11_vs()
{
	return _shader;
}

ID3D11InputLayout* Render::VertexShader::get_d11_il()
{
	return _layout;
}

Render::VertexShader::VertexShader(Core::GraphicsContext* ctx, const wchar_t* file_name,const D3D11_INPUT_ELEMENT_DESC* layout,
	UINT num_elements)
	: IShader(ctx)
	, _shader(nullptr)
	, _layout(nullptr)
{
	ID3DBlob* blob;
	D3DReadFileToBlob(file_name, &blob);

	if(blob)
	{
		construct(blob);
		link(blob, layout, num_elements);

		blob->Release();
	}
}

void Render::VertexShader::bind()
{
	context->get_context()->set_vertex_shader(this);
}
