#pragma once
#include <Windows.h>
#include "InteractionEventHandler.h"

namespace UI
{
	namespace Interaction
	{
		class __declspec(dllexport) WinIntEventHandler : public IEventHandler
		{
		public:
			void windowProc(UINT msg, WPARAM wParam, LPARAM lParam);
		};
	}
}
