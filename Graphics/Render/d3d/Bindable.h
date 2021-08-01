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
		Bindable(Core::GraphicsContext*engine);
		virtual ~Bindable();

		virtual void bind() = 0;
	};
}
