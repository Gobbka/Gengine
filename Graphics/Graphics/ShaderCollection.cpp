﻿#include "ShaderCollection.h"
#include "../Render/d3d/Shader/IShader.h"

ShaderCollection::ShaderCollection(Render::GEGraphics* graphics)
	: _graphics(graphics)
{
}

void ShaderCollection::insert(const wchar_t* file_name, Render::IShader* shader)
{
	_collection[file_name] = shader;
}

Render::VertexShader* ShaderCollection::get_vs(const wchar_t* file_name)
{
	return (Render::VertexShader*)_collection[file_name];
}
