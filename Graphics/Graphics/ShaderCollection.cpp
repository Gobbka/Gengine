#include "ShaderCollection.h"
#include "../Render/d3d/Shader/Shader.h"

ShaderCollection::ShaderCollection(Core::GraphicsContext* context)
{
	_context = context;
}

void ShaderCollection::insert(const wchar_t* file_name, Render::Shader* shader)
{
	_collection[file_name] = shader;
}
