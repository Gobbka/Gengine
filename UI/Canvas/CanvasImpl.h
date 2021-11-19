#pragma once
#include <vector>
#include "D11VertexAllocator.h"
#include "DrawData.h"
#include "Objects/IObject.h"

namespace Render
{
	class VertexShader;
	class PixelShader;
}

namespace Canvas {
	struct CanvasBackupData
	{
		Render::PixelShader* old_ps;
		Render::VertexShader* old_vs;
	};

	class __declspec(dllexport) CanvasImpl final {
		CanvasBackupData _backupData;
		DrawData _drawData;
		Render::D11VertexAllocator _canvas;
		std::vector<IObject*> _objects;
	public:
		UI::Vertex2D* vertices() const;

		DrawData* begin();
		void present() const;

		CanvasImpl(Core::GraphicsContext*engine);
		CanvasImpl() = delete;
		~CanvasImpl() = default;

		void update() const;
		void render(Render::DrawEvent2D* event);

		void add_object(IObject* object);

		void bind() const;
	};
}
