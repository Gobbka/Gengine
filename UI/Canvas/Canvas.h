#pragma once
#include <vector>
#include "D11VertexAllocator.h"
#include "Objects/IObject.h"

namespace Canvas {
	class __declspec(dllexport) Canvas final {
		Render::D11VertexAllocator _canvas;
		std::vector<IObject*> _objects;
	protected:
		void render_components(Render::DrawEvent2D* event);
	public:
		UI::Vertex2D* vertices() const;
		
		Canvas(Core::GraphicsContext*engine);
		~Canvas();

		void update() const;
		void render(Render::DrawEvent2D* event);

		void add_object(IObject* object);

		void bind();
	};
}