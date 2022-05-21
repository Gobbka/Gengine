#pragma once
#include "GEPostEffect.h"

namespace Render {
	class SmoothPostEffect : public GEPostEffect
	{
	public:
		SmoothPostEffect(GEGraphics* gfx);
		void execute(Scene* scene) override;
	};
}