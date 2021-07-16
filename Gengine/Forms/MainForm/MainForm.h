#pragma once
#include "../Form/Form.h"
namespace Core {
	class GraphicsContext;
}

namespace UI {
	class Panel;
}

namespace Forms
{
	class MainForm : public Core::Form
	{
	private:
		UI::Panel* topbar_panel;
	public:
		MainForm(HINSTANCE hinst, UINT width, UINT height);

		void initialize_components(Core::GraphicsContext*graphics);
	};
}
