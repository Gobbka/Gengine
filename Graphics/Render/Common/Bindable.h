#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	class Camera;

	class __declspec(dllexport) Bindable
	{
	protected:
		Core::GraphicsContext* _engine;
	public:
		Bindable(Core::GraphicsContext*engine)
			: _engine(engine)
		{}

		virtual ~Bindable() = default;

		virtual void bind() = 0;
	};
}
