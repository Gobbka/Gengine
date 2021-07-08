#pragma once
#include "InteractionEventHandler.h"

namespace UI
{
	namespace Interaction
	{
		class __declspec(dllexport) WinIntEventHandler : public UI::Interaction::IEventHandler
		{
		public:
			void window_proc(UINT msg, WPARAM wParam, LPARAM lParam);
		};
	}
}
