#pragma once
#include <vector>

#include "D3D11Canvas.h"
#include "../Render/Layer/ILayer.h"

namespace Canvas {
	class __declspec(dllexport) Canvas2DLayer : public Render::ILayer {
	private:
		Render::D3D11Canvas _canvas;
		std::vector<I2DCanvasObject*> _objects;
	public:
		Render::Vertex* vertices() const;
		
		Canvas2DLayer(Render::D3DEngine*engine);
		
		void update() override;
		void render(Render::DrawEvent* event) override;

		Render::D3D11Canvas* canvas();

		void add_object(I2DCanvasObject* object);
	};
}
