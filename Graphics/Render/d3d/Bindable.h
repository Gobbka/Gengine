#pragma once

namespace Render
{
	class D3DEngine;

	class Bindable
	{
	protected:
		D3DEngine* _engine;
	public:
		Bindable(D3DEngine*engine);
		virtual ~Bindable();

		virtual void bind() = 0;
	};
}
