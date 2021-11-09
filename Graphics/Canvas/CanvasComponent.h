#pragma once
#include <vector>
#include "D11VertexAllocator.h"
#include "Objects/I2DCanvasObject.h"

namespace Canvas {
	class __declspec(dllexport) CanvasComponent {
	private:
		Render::D11VertexAllocator _canvas;
		std::vector<I2DCanvasObject*> _objects;

		bool _hidden;
	protected:
		virtual void render_components(Render::DrawEvent2D* event);
	public:
		Render::Vertex* vertices() const;
		
		CanvasComponent(Core::GraphicsContext*engine);
		virtual ~CanvasComponent();

		void update() const;
		void render(Render::DrawEvent2D* event);

		void add_object(I2DCanvasObject* object);

		bool hidden() { return _hidden; }
		void hide() { _hidden = true; }
		void show() { _hidden = false; }
	};
}
