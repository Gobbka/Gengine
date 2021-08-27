﻿#pragma once
#include <vector>


#include "Animation/Animator.h"
#include "Ecs/Ecs.h"
#include "Events/WinIntEventHandler.h"
#include "Types/Types.h"

namespace Core {
	class GraphicsContext;
}

namespace Render {
	class Camera;
}

namespace UI {
	class InteractiveForm;

	class __declspec(dllexport) UIContext : public Interaction::WinIntEventHandler
	{
	private:
		std::vector<InteractiveForm*> _forms;
		Core::GraphicsContext* _gfx;
		Vector2 _cursor;
		Animator _animator;
	public:
		explicit UIContext(Core::GraphicsContext*gfx);
		
		ECS::Entity* create_layer();

		Animator* animator();
	protected:
		void on_lbmouse_down() override;
		void on_lbmouse_up() override;
		void on_mouse_scroll(short direction) override;
		void on_mouse_move(int mx, int my) override;
		void on_db_click() override;
		
	};
}