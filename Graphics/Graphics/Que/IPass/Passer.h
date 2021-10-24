#pragma once
#include <vector>
#include "IPass.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render {
	
	class __declspec(dllexport) Passer
	{
		std::vector<IPass*> _begin_passes;
		std::vector<IPass*> _probe_passes;
		std::vector<IPass*> _draw_passes;
		std::vector<IPass*> _end_passes;
		std::vector<IPass*> _overlay_passes;
		std::vector<IPass*> _present_passes;
		
		friend Core::GraphicsContext;
	public:
		void add_pass(IPass*,PassStep step=PassStep::draw);
	};
}
