#pragma once

namespace Render
{
	enum class PassStep
	{
		probe,
		draw,
		overlay
	};
	
	class __declspec(dllexport) IPass
	{
	public:
		virtual void execute() = 0;
	};
}
