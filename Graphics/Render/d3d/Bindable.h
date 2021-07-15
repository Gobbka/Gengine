#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Camera;

	class Bindable
	{
	protected:
		Core::GraphicsContext* _engine;
	public:
		Bindable(Core::GraphicsContext*engine);
		virtual ~Bindable();

		virtual void bind() = 0;
	};
}
