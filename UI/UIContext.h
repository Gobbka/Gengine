#pragma once
#include <vector>
#include "Ecs/Ecs.h"
#include "Events/WinIntEventHandler.h"
#include "Types/Types.h"

namespace Core {
	class DX11Graphics;
}

namespace Render {
	class Scene;
	class Camera;
}

namespace UI {
	class InteractiveForm;

	class __declspec(dllexport) UIContext : public Interaction::WinIntEventHandler
	{
	private:
		std::vector<InteractiveForm*> _forms;
		Core::DX11Graphics* _gfx;
		Vector2 _cursor;
	public:
		UIContext(Core::DX11Graphics*gfx,Render::Scene*scene);
		
		ECS::Entity* create_layer();
	protected:
		void on_lbmouse_down() override;
		void on_lbmouse_up() override;
		void on_mouse_scroll(short direction) override;
		void on_mouse_move(int mx, int my) override;
		void on_db_click() override;
	};
}
