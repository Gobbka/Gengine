#pragma once
#include <d3d11.h>
#include "../Bindable.h"

namespace Render {
	class SamplerState : Bindable
	{
		ID3D11SamplerState* _state;
	public:
		SamplerState(Core::GraphicsContext* engine);

		void bind() override;
	};
}
