#pragma once
#include <map>
#include "../Render/d3d/Shader/IShader.h"
#include "../Render/d3d/Shader/PixelShader.h"
#include "../Render/Common/GraphicsCommon.h"

namespace Render
{
	class VertexShader;
	class IShader;
}

class __declspec(dllexport) ShaderCollection
{
	std::map<const wchar_t*, Render::IShader*> _collection;
	Render::GEGraphics* _graphics;
public:
	explicit ShaderCollection(Render::GEGraphics* graphics);

	void insert(const wchar_t* file_name, Render::IShader* shader);

	Render::VertexShader* get_vs(const wchar_t* file_name);

	template<typename T>
	T* get(const wchar_t* file_name)
	{
		auto* shader = _collection[file_name];
		if (shader != nullptr)
			return (T*)shader;

		shader = new T(_graphics,file_name);

		insert(file_name, shader);

		return (T*)shader;
	}
};
