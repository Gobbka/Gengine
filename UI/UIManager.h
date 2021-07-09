#pragma once
#include <vector>

#include "Events/WinIntEventHandler.h"
#include "Graphics/Types.h"
struct Position2;

namespace Render {
	class D3DEngine;
}

namespace UI {
	class InteractiveForm;

	class __declspec(dllexport) UIManager : public Interaction::WinIntEventHandler
	{
	private:
		std::vector<InteractiveForm*> _forms;
		Position2 _cursor;

		UIManager();
	public:
		static UIManager* instance();
		InteractiveForm* create_layer(Render::D3DEngine* engine);
	protected:
		void on_lbmouse_down() override;
		void on_lbmouse_up() override;
		void on_mouse_scroll(short direction) override;
		void on_mouse_move(int mx, int my) override;
	};
}
