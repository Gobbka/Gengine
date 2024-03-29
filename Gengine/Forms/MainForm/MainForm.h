#pragma once
#include "../Form/Form.h"

namespace Render {
	class Camera;
}

namespace UI {
	class InteractiveElement;
	class FlexColumnPanel;
	class FlexRowPanel;
	class Panel;
}

namespace Forms
{
	class MainForm : public GE::Form
	{
		void print_element(UI::InteractiveElement* element,UINT deep);
		void print_gpu_info();
		void print_entity();
	private:
		UI::FlexRowPanel* _topbar_panel;
		UI::FlexColumnPanel* _worldspace_panel;
		UI::FlexColumnPanel* _assets_panel_wrapper;
		UI::FlexRowPanel* _assets_panel;
		UI::Panel* _render_panel;

		Render::GETexture* _folder_texture;
		Render::GETexture* _file_texture;
	public:
		Render::Scene* editorScene;

		MainForm(HINSTANCE hinst, UINT width, UINT height);

		void scan_assets_directory();

		void handle_resize(Surface rect) override;

		void update() override;
	};
}
