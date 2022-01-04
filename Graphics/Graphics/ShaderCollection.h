#pragma once
#include <map>
#include "../Render/d3d/Shader/IShader.h"
#include "../Render/d3d/Shader/PixelShader.h"

namespace Core
{
	class DX11Graphics;
}

namespace Render
{
	class VertexShader;
	class IShader;
}

class __declspec(dllexport) ShaderCollection
{
	std::map<const wchar_t*, Render::IShader*> _collection;
	Core::DX11Graphics* _context;
public:
	explicit ShaderCollection(Core::DX11Graphics* context);

	void insert(const wchar_t* file_name, Render::IShader* shader);

	Render::VertexShader* get_vs(const wchar_t* file_name);

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
