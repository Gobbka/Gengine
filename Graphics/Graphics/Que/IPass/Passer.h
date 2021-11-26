#pragma once
#include <vector>
#include "IPass.h"

namespace Render {

	enum class PassStep
	{
		begin,
		probe,
		draw,
		overlay
	};

	class __declspec(dllexport) Passer
	{
		std::vector<IPass*> _begin_passes;
		std::vector<IPass*> _probe_passes;
		std::vector<IPass*> _draw_passes;
		std::vector<IPass*> _overlay_passes;
	public:

		void execute(Scene*scene);
		void add_pass(IPass*,PassStep step);
	};
}
