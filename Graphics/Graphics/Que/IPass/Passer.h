#pragma once
#include "../../../Graphics.h"

namespace Render {
	class Passer
	{
		std::vector<IPass*> _begin_passes;
		std::vector<IPass*> _body_passes;
		std::vector<IPass*> _end_passes;
		
		friend Core::GraphicsContext;
	public:
		void add_pass(IPass*);

		std::vector<IPass*>& get_passes();
	};
}
