#include "VertexShader.h"
#include "../../../Render/Engine/Camera.h"

void Render::VertexShader::construct(ID3DBlob* shader_blob)
{
	_engine->device()->CreateVertexShader(
		shader_blob->GetBufferPointer(),
		shader_blob->GetBufferSize(),
		nullptr,
		&_shader
	);
}

void Render::VertexShader::create_input_layout(const D3D11_INPUT_ELEMENT_DESC* elements, UINT num_elements,
	ID3D11InputLayout** layout)
{
	_engine->device()->CreateInputLayout(
		elements,
		num_elements,
		_blob->GetBufferPointer(),
		_blob->GetBufferSize(),
		layout
	);
}

Render::VertexShader::VertexShader(Core::GraphicsContext* engine)
	: Shader(engine)
{
	_shader = nullptr;
}

void Render::VertexShader::bind()
{
	_engine->context()->VSSetShader(_shader, nullptr, 0);
}
