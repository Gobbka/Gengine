#pragma once
#include "../Events/RenderEvent.h"

namespace Render {
	class ILayer
	{
	private:
		bool _hidden = false;
	public:
		virtual ~ILayer() = default;

		
		void hide() { _hidden = true; }
		void show() { _hidden = false; }
		bool hidden() const { return _hidden; }

		virtual void update() = 0;
		virtual void render(Render::DrawEvent* event) = 0;
	};
}