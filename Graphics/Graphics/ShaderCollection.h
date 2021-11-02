#pragma once
#include <map>
#include "../Render/d3d/Shader/PixelShader.h"
#include "../Render/d3d/Shader/IShader.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class IShader;
}

class ShaderCollection
{
	std::map<const wchar_t*, Render::IShader*> _collection;
	Core::GraphicsContext* _context;
public:
	explicit ShaderCollection(Core::GraphicsContext* context);

	void insert(const wchar_t* file_name, Render::IShader* shader);

	template<typename T>
	T* get(const wchar_t* file_name)
	{
		auto* shader = _collection[file_name];
		if (shader != nullptr)
			return (T*)shader;

		shader = new T(_context,file_name);

		insert(file_name, shader);

		return (T*)shader;
	}
};
