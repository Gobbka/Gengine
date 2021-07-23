#pragma once
#include <vector>

#include "D3D11Canvas.h"
#include "../Render/Layer/ILayer.h"

namespace Canvas {
	class __declspec(dllexport) Canvas2DLayer : public Render::ILayer {
	private:
		Render::D3D11Canvas _canvas;
		std::vector<I2DCanvasObject*> _objects;
	protected:
		virtual void render_components(Render::DrawEvent2D* event);
	public:
		Render::Vertex* vertices() const;
		
		Canvas2DLayer(Core::GraphicsContext*engine);
		
		void update() override;
		void render(Render::DrawEvent2D* event) override;

		Render::D3D11Canvas* canvas();

		void add_object(I2DCanvasObject* object);
	};
}
