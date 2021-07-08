#pragma once
#include "InteractionEventHandler.h"

namespace Application
{
	namespace Interaction
	{
		class WinIntEventHandler : public UI::Interaction::IEventHandler
		{
		public:
			void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
		};
	}
}
