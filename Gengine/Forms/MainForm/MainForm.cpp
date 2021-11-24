#include "MainForm.h"

#include <FreeImage.h>
#include <Window/Keyboard.h>
#include <FS/FSObject.h>
#include <FS/FSDirectory.h>

#include <Graphics.h>
#include <Render/Engine/Camera.h>
#include <InteractiveForm.h>
#include <Loaders/AssetsLoader.h>

#include <UIContext.h>
#include <UI/Button.h>
#include <UI/Panel.h>
#include <UI/FlexColumnPanel.h>
#include <UI/FlexRowPanel.h>
#include <UI/Text.h>

#include "Animation/Animator.h"
#include "Graphics/SpriteFont.h"
#include "Logger/Logger.h"

namespace UI
{
	class Directory : public Panel
	{
	private:
		FS::FSObject _object;
	public:
		Directory(FS::FSObject object, Position2 position, Surface resolution, Render::Texture* texture)
			: Panel(position, resolution, nullptr),
			_object(object)
		{
			Panel::set_texture(texture);
			
		}

		void handle_db_click() override
		{
			if(!_object.is_directory())
			{
				std::wstring command(L"start ");
				command += _object.path();
				
				_wsystem(command.c_str());
			}
		}

		void handle_mouse_enter() override
		{
			SetCursor(LoadCursor(0, IDC_HAND));
			Panel::handle_mouse_enter();
		}

		void handle_mouse_leave() override
		{
			SetCursor(LoadCursor(0, IDC_ARROW));
			Panel::handle_mouse_leave();
		}
		
		
	};
}

Forms::MainForm::MainForm(HINSTANCE hinst, UINT width, UINT height)
	: Form(hinst, width, height)
	, _topbar_panel(new UI::FlexColumnPanel({0, 0}, {(float)width, 30}, {RGB_TO_FLOAT(26, 26, 26)}))
	, _worldspace_panel(new UI::FlexColumnPanel({0, -30}, {250, (float)height - 30.f}, {RGB_TO_FLOAT(20, 20, 20)}))
	, _assets_panel_wrapper(new UI::FlexColumnPanel({250, -1 * (float)height + 250.f}, {(float)width - 250, 250},{RGB_TO_FLOAT(26, 26, 26)}))
	, _assets_panel(new UI::FlexRowPanel({0, 0}, {(float)width - 250, 250 - 30}, {RGB_TO_FLOAT(26, 26, 26)})),
	_render_panel(new UI::Panel({250, -30}, {897, 500}, nullptr)), editorScene(get_graphics_context()->create_scene())
{
	auto* font = new Render::SpriteFont(get_graphics_context()->get_device(), L"visby.spritefont");

	main_scene->register_system(new UI::HandleAnimationSystem());
	const auto main_cam = main_scene->get_main_camera()->get<Render::Camera>();
	main_cam->get_target_view()->clear_color = Color3XM(.05f, .05f, .05f);

	auto* uicanvas_entity = get_ui()->create_layer();

	_worldspace_panel->add_element(new UI::Button({ 0,0 }, { 0,50 }, { RGB_TO_FLOAT(48,48,48)}, font,L"Create nigger"));

	_assets_panel_wrapper->add_element(
		(new UI::FlexRowPanel({ 0,0 }, { (float)width - 450,30 }, { RGB_TO_FLOAT(34,34,34) }))
		->add_element(new UI::Text(font,L"Assets",{0,0}))
	);

	_assets_panel_wrapper->add_element(_assets_panel);

	auto folder_material = AssetsLoader::load_png(L"assets\\folder.png");
	auto file_material = AssetsLoader::load_png(L"assets\\file.png");

	_folder_texture = get_graphics_context()->get_device()->create_texture(folder_material);
	_file_texture = get_graphics_context()->get_device()->create_texture(file_material);

	auto worldTexture = new Render::RenderTarget(get_graphics_context(),{1400,780});
	auto* editorCam = editorScene->create_camera(worldTexture);
	editorScene->set_main_camera(editorCam);
	auto cam = editorCam->get<Render::Camera>();
	cam->get_target_view()->clear_color.a = 0.f;

	_render_panel->set_texture(worldTexture->get_texture());

	_topbar_panel->add_element(new UI::Text(font, L"GEngine",{0,0}));
	
	auto uicanvas = uicanvas_entity->get<UI::InteractiveForm>();
	
	uicanvas
		->add_element(_topbar_panel)
		->add_element(_worldspace_panel)
		->add_element(_render_panel)
		->add_element(_assets_panel_wrapper)
	;
	
	scan_assets_directory();
}

void Forms::MainForm::scan_assets_directory()
{
	FS::FSDirectory directory((wchar_t*)L"assets");

	directory.foreach([&](FS::FSObject* file)
	{
		Render::Texture* lp_texture = file->is_directory() ? _folder_texture : _file_texture;
		
		auto* panel = new UI::Directory(*file, { 0,0 }, { 120,120 }, lp_texture);
		
		_assets_panel->add_element(panel);
	});

}

void Forms::MainForm::handle_resize(Surface rect)
{
	auto width = rect.width;
	auto height = rect.height;
	
	_topbar_panel->set_resolution(Surface(width, 30));
	_worldspace_panel->set_resolution(Surface(250, height - 30));
	
	Form::handle_resize(rect);
}

void Forms::MainForm::update()
{
	static float scale = 45.f;
	auto camera = editorScene->get_main_camera()->get<Render::Camera>();
	
	if (keyboard->pressed(VirtualKey::KEY_W)) // W
	{
		camera->adjust_position_relative(Position3(0.05f, 0, 0));
	}
	if (keyboard->pressed(VirtualKey::KEY_S))
	{
		camera->adjust_position_relative(Position3(-0.05f, 0, 0));
	}
	if (keyboard->pressed(VirtualKey::KEY_D))
	{
		camera->adjust_position_relative(Position3(0, 0, 0.05f));
	}
	if (keyboard->pressed(VirtualKey::KEY_A))
	{
		camera->adjust_position_relative(Position3(0, 0, -0.05f));
	}
	if (keyboard->pressed(VirtualKey::SPACE))
	{
		camera->set_fov(scale);
		scale += 0.1f;
	}
	if (keyboard->pressed(VirtualKey::CONTROL))
	{
		camera->set_fov(scale);
		scale -= 0.1f;
	}
	if (keyboard->pressed(VirtualKey::LEFT))
	{
		camera->adjust_rotation((Vector3(0, -0.04f, 0)));
	}
	if (keyboard->pressed(VirtualKey::RIGHT))
	{
		camera->adjust_rotation((Vector3(0, 0.04f, 0)));
	}
	if (keyboard->pressed(VirtualKey::UP))
	{
		camera->adjust_rotation((Vector3(-0.04f, 0, 0)));
	}
	if (keyboard->pressed(VirtualKey::DOWN))
	{
		camera->adjust_rotation((Vector3(0.04f, 0, 0)));
	}
	if(keyboard->pressed(VirtualKey::F1))
	{
		char command[12];
		std::cout << "Send command to MainForm: \n>> ";
		scanf("%12s", command);
		if(strcmp(command,"dom")==0)
		{
			main_scene->world()->each<UI::InteractiveForm>([&](ECS::Entity* ent, ECS::ComponentHandle<UI::InteractiveForm>form)
				{
					std::cout << "=== Interactive From ===\n";
					form->foreach([&](UI::InteractiveElement* element)
						{
							print_element(element,0);
						});
				});
		}
		if(strcmp(command,"gpu")==0)
		{
			print_gpu_info();
		}
		if(strcmp(command,"entity")==0)
		{
			print_entity();
		}
	}
}

void Forms::MainForm::print_element(UI::InteractiveElement* element,UINT deep)
{
	for(int i = 0;i<=deep;i++)
	{
		std::cout << '-';
	}
	auto desc = element->get_desc();
	auto pos = element->get_position();
	auto res = element->get_resolution();
	std::cout
		<< " " << green << desc.string_name << white
		<< " (x:"<<yellow<<pos.x<<white
		<< " y:" <<yellow<<pos.y<<white
		<< ")" << " (w:" << yellow << res.width << white
		<< " h:"<<yellow<<res.height<<white<<")\n";
	if(desc.can_be_parent)
	{
		for(auto*child:*((UI::Parent*)element)->children())
		{
			print_element(child, deep + 1);
		}
	}
}

void Forms::MainForm::print_gpu_info()
{
	IDXGIDevice* dev;
	IDXGIAdapter* adapter;
	DXGI_ADAPTER_DESC desc;

	get_graphics_context()->device->QueryInterface(__uuidof(IDXGIDevice), (void**) & dev);
	dev->GetAdapter(&adapter);
	adapter->GetDesc(&desc);
	std::cout << "=== GPU ===\n";
	std::wcout << L"Name: " << desc.Description << '\n';
	std::cout << "Memory: "<< green << desc.DedicatedVideoMemory / 1048576u <<white << "MB\n";
	adapter->GetDesc(&desc);
	if (adapter)
		adapter->Release();
	if (dev)
		dev->Release();
}

void Forms::MainForm::print_entity()
{
	std::cout << "Entity list: \n";
	editorScene->world()->all([&](ECS::Entity* ent)
		{
			std::cout << '[' << ent->getEntityId() << "] ";
		});
	std::cout << "\nChoose entity? (enter entity id or 0 to close)\n>>";
	int id=0;
	scanf("%d", &id);
	if(id != ECS::Entity::InvalidEntityId)
	{
		char command[20];
		std::cout << "Available commands:\ndel (delete entity)\nEnter command\n>>";
		scanf("%20s", command);
		if(strcmp(command,"del")==0)
		{
			editorScene->world()->destroy( editorScene->world()->getById(id));
		}
	}
}
