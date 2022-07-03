#pragma once
#include "Ecs/Ecs.h"
#include "Events/WinIntEventHandler.h"
#include "Render/Common/GraphicsCommon.h"
#include "Types/Types.h"

namespace Render {
	class Scene;
	class Camera;
}

namespace UI {
	enum class MouseButton;
	class InteractiveForm;

	class __declspec(dllexport) UIContext : public Interaction::WinIntEventHandler
	{
	private:
		Render::GEGraphics* _gfx;
		Vector2 _cursor;
	public:
		UIContext(Render::GEGraphics*gfx,Render::Scene*scene);
		
		ECS::Entity* createLayer();
	protected:
		void onMouseDown(MouseButton button) override;
		void onMouseUp(MouseButton button) override;
		void onMouseScroll(short direction) override;
		void onMouseMove(int mx, int my) override;
		void onDbClick() override;
	};
}
