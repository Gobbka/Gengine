#include "UIManager.h"
#include "InteractiveForm.h"
UI::InteractiveForm* UI::UIManager::create_layer(Render::D3DEngine* engine, Position2* lp_cursor)
{
	return new InteractiveForm(engine, lp_cursor);
}
