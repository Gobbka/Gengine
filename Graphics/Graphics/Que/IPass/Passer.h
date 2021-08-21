﻿#pragma once
#include <vector>
#include "IPass.h"

namespace Render {
	
	class Passer
	{
		std::vector<IPass*> _begin_passes;
		std::vector<IPass*> _probe_passes;
		std::vector<IPass*> _draw_passes;
		std::vector<IPass*> _end_passes;
		std::vector<IPass*> _present_passes;
		
		friend Core::GraphicsContext;
	public:
		void add_pass(IPass*,PassStep step=PassStep::draw);
		void remove_pass(IPass*, PassStep from = PassStep::draw);
	};
}
