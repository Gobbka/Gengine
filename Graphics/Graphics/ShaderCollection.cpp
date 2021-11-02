#include "ShaderCollection.h"
#include "../Render/d3d/Shader/IShader.h"

ShaderCollection::ShaderCollection(Core::GraphicsContext* context)
{
	_context = context;
}

void ShaderCollection::insert(const wchar_t* file_name, Render::IShader* shader)
{
	_collection[file_name] = shader;
}
