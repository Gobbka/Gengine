#pragma once

namespace Render
{
	enum class PassStep
	{
		probe,
		draw,
		overlay
	};

	class Scene;

	class __declspec(dllexport) IPass
	{
	public:
		virtual void execute(Scene*scene) = 0;
	};
}
