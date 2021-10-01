#pragma once
#include <map>
#include "../Render/d3d/Shader/PixelShader.h"
#include "../Render/d3d/Shader/Shader.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class Shader;
}

class ShaderCollection
{
	std::map<const wchar_t*, Render::Shader*> _collection;
	Core::GraphicsContext* _context;
public:
	explicit ShaderCollection(Core::GraphicsContext* context);

	void insert(const wchar_t* file_name, Render::Shader* shader);

	template<typename T>
	T* get(const wchar_t* file_name)
	{
		auto* shader = _collection[file_name];
		if (shader != nullptr)
			return (T*)shader;

		shader = new T(_context);
		shader->read_file(file_name);
		shader->release_blob();

		insert(file_name, shader);

		return (T*)shader;
	}
};
