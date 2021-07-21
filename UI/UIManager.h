#pragma once
#include <vector>


#include "Animation/Animator.h"
#include "Events/WinIntEventHandler.h"
#include "Types/Types.h"

namespace Render {
	class Camera;
}

namespace UI {
	class InteractiveForm;

	class __declspec(dllexport) UIManager : public Interaction::WinIntEventHandler
	{
	private:
		std::vector<InteractiveForm*> _forms;
		Vector2 _cursor;
		Animator _animator;

		UIManager();
	public:
		static UIManager* instance();
		InteractiveForm* create_layer(Render::Camera* engine);

		Animator* animator();
	protected:
		void on_lbmouse_down() override;
		void on_lbmouse_up() override;
		void on_mouse_scroll(short direction) override;
		void on_mouse_move(int mx, int my) override;
		void on_db_click() override;
		
	};
}
