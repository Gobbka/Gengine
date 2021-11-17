#pragma once
#include "Types/Types.h"

namespace UI
{
	struct Vertex2D;
}

namespace Render {
	struct DrawEvent2D;
	class Texture;
	struct DrawEvent;
}

namespace Canvas {
	class Canvas;

	class __declspec(dllexport) IControllable
	{
	protected:
		virtual void on_initialize() = 0;
	public:
		virtual ~IControllable() = default;
		IControllable() = default;

		bool hidden = false;

		virtual void draw(Render::DrawEvent2D* event) = 0;

		virtual void      set_position(Position2 pos) = 0;
		virtual Position2 get_position() = 0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void set_texture(Render::Texture* texture) PURE;

		virtual void move_by(Position2) = 0;
	};

	typedef unsigned long INDEX;

	class __declspec(dllexport) IObject : public IControllable
	{
		Canvas* _canvas = nullptr;
		INDEX _index = 0u;
	public:
		void initialize(Canvas*canvas);

		auto get_index() const { return _index; }
		Canvas* canvas();
		UI::Vertex2D* vertices() const;

		void set_index(INDEX new_index) { _index = new_index; }

		// must return needed object vertex length
		virtual INDEX size() = 0;
	};
}
