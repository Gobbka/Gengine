#pragma once
#include "../../Graphics/Types.h"

namespace Render {
	struct Vertex;
	struct DrawEvent;
}

namespace Canvas {
	class Canvas2DLayer;
	
	// IControllableObject -> D3DObject -> 

	class __declspec(dllexport) IControllableObject
	{
	private:
		Canvas2DLayer* _layer;
	protected:
		Canvas2DLayer* layer() const;

		virtual void init() = 0;

	public:
		bool hidden = false;

		virtual void draw(Render::DrawEvent* event) = 0;

		virtual void      set_position(Position2 pos) = 0;
		virtual Position2 get_position() = 0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void    set_color(Color4 color) = 0;
		virtual Color4  get_color() = 0;


		virtual void move_by(Position2) = 0;

		void initialize(Canvas2DLayer* layer);

		IControllableObject();
	};

	class I2DCanvasObject : public IControllableObject
	{
	public:
		Render::Vertex* vertices() const;

	public:
		typedef unsigned long INDEX;
	protected:
		INDEX _index = 0u;
	public:
		auto get_index() const { return _index; }
		void set_index(INDEX new_index) { _index = new_index; }

		// must return needed object vertex length
		virtual INDEX size() = 0;

	};
}
