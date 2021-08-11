#pragma once
#include <vector>

#include "D3D11Canvas.h"
#include "Objects/I2DCanvasObject.h"

namespace Canvas {
	class __declspec(dllexport) Canvas2DLayer {
	private:
		Render::D3D11Canvas _canvas;
		std::vector<I2DCanvasObject*> _objects;

		bool _hidden;
	protected:
		virtual void render_components(Render::DrawEvent2D* event);
	public:
		Render::Vertex* vertices() const;
		
		Canvas2DLayer(Core::GraphicsContext*engine);
		
		void update();
		void render(Render::DrawEvent2D* event);

		Render::D3D11Canvas* canvas();

		void add_object(I2DCanvasObject* object);

		bool hidden() { return _hidden; }
		void hide() { _hidden = true; }
		void show() { _hidden = false; }
	};
}
