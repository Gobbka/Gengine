#pragma once
#include "../Form/Form.h"
namespace Forms
{
	class WelcomeForm final : public GE::Form
	{
	public:
		WelcomeForm(HINSTANCE hinst);
		void update() override;
	};
}
