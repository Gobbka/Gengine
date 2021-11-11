#pragma once
#include "Types/Types.h"

namespace Render {
	struct DrawEvent2D;
	class Texture;
	struct Vertex;
	struct DrawEvent;
}

namespace Canvas {
	class Canvas;

	class __declspec(dllexport) IControllable
	{
	private:
		Canvas* _layer;
	protected:
		Canvas* layer() const;

		virtual void on_initialize() = 0;
	public:
		virtual ~IControllable() = default;
		bool hidden = false;

		virtual void draw(Render::DrawEvent2D* event) = 0;

		virtual void      set_position(Position2 pos) = 0;
		virtual Position2 get_position() = 0;

		virtual void    set_resolution(Surface surface) = 0;
		virtual Surface get_resolution() = 0;

		virtual void set_texture(Render::Texture* texture) PURE;

		virtual void scale(float value) =0;

		virtual void move_by(Position2) = 0;

		void initialize(Canvas* layer);

		IControllable();
	};

	class __declspec(dllexport) IObject : public IControllable
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

		// todo: fix scaling
		void scale(float value) override;

		// must return needed object vertex length
		virtual INDEX size() = 0;

	};
}
