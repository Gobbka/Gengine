#pragma once

namespace Core {
	class DX11Graphics;
}

namespace Render
{
	class __declspec(dllexport) Bindable
	{
	protected:
		Core::DX11Graphics* _engine;
	public:
		Bindable(Core::DX11Graphics*engine)
			: _engine(engine)
		{}

		virtual ~Bindable() = default;

		virtual void bind() = 0;
	};
}
