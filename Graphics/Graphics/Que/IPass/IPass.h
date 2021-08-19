#pragma once

namespace Render
{
	class __declspec(dllexport) IPass
	{
	public:
		virtual void execute() = 0;
	};
}
