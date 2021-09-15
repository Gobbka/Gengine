#pragma once
#include <d3d11.h>
#include "../Bindable.h"

namespace Render {
	enum class SamplerFilter
	{
		MinMagMip,
		Anisotropic,
	};

	class SamplerState : Bindable
	{
		ID3D11SamplerState* _state;
	public:
		SamplerState(Core::GraphicsContext* engine,SamplerFilter filter = SamplerFilter::Anisotropic);

		void bind() override;
	};
}
