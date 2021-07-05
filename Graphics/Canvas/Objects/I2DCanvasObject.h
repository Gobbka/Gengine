#pragma once
#include "../../Render/d3d/D3DObjectDescription.h"

#include "../../Graphics/Types.h"

namespace Render {
	struct Vertex;
	struct DrawEvent;
}

namespace Canvas {
	class Canvas2DLayer;

	class I2DCanvasObject : public Render::D3DObjectDescription
	{
	private:
		Canvas2DLayer* _layer;
	protected:
		Canvas2DLayer* layer() const;
		
		virtual void init() =0;

		Render::Vertex* vertices() const;
	public:
		virtual void draw(Render::DrawEvent*event) =0;

		virtual void      set_position(Position2 pos) =0;
		virtual Position2 get_position() =0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void    set_color(Color4 color) = 0;
		virtual Color4  get_color() = 0;

		
		
		virtual void move_by(Position2) = 0;

		void initialize(Canvas2DLayer*layer);
		
		I2DCanvasObject();
	};
}
