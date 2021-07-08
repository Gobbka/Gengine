#pragma once
struct Position2;

namespace Render {
	class D3DEngine;
}

namespace UI {
	class InteractiveForm;

	class __declspec(dllexport) UIManager
	{
	public:
		static InteractiveForm* create_layer(Render::D3DEngine* engine,Position2*lp_cursor);
	};
}
