#pragma once

namespace Render
{
	class Scene;

	class __declspec(dllexport) IPass
	{
	public:
		virtual void execute(Scene*scene) = 0;
	};
}
