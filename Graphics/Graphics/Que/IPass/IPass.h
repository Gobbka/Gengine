#pragma once

namespace Core {
	class GraphicsContext;
}

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
		virtual void execute(Core::GraphicsContext*context) = 0;
	};
}
