#pragma once
#include "../Bindable.h"
#include <d3d11.h>
namespace Render {
	class Shader
	{

	protected:
		ID3DBlob* _blob = nullptr;
		Core::GraphicsContext* context;

		virtual void construct(ID3DBlob* shader_blob) PURE;
		explicit Shader(Core::GraphicsContext* engine) : context(engine) {}
	public:

		void read_file(const wchar_t* file_name);
		void release_blob() const;
	};
}
