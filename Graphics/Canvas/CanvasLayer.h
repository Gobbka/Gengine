#pragma once
#include "D3D11Canvas.h"
#include "../Render/Layer/ILayer.h"

namespace Canvas {
	class CanvasLayer : public Render::ILayer {
	private:
		Render::D3D11Canvas _canvas;
		
	public:
		CanvasLayer(Render::D3DEngine*engine);
		
		void update() override;
		void render(Render::DrawEvent* event) override;

		Render::D3D11Canvas* canvas();
	};
}
