#include "WelcomeForm.h"

#include "Graphics.h"
#include "InteractiveForm.h"
#include "UIContext.h"
#include "Graphics/SpriteFont.h"
#include "Render/Engine/Camera.h"
#include "Render/Engine/RenderTarget.h"
#include "UI/Text.h"

Forms::WelcomeForm::WelcomeForm(HINSTANCE hinst)
	: Form(TEXT("Welcome!"),hinst,400,500)
{
	const auto main_cam = main_scene->get_main_camera()->get<Render::Camera>();
	main_cam->get_target_view()->clear_color = Color3XM::from_rgb(26,26,26);

	auto* font = new Render::SpriteFont(get_graphics_context()->get_device(), L"visby.spritefont");
	auto uicanvas = get_ui()->create_layer()->get<UI::InteractiveForm>();

	uicanvas->add_element(new UI::Text(font, L"Welcome to GEngine!", { 0,0 }));
}

void Forms::WelcomeForm::update()
{

}
