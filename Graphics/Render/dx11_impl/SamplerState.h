#pragma once
#include <d3d11.h>
#include "../Common/Bindable.h"

namespace Render
{
	enum class SamplerFilter
	{
		MinMagMip,
		Anisotropic,
	};

	class DX11SamplerState : Bindable
	{
		ID3D11SamplerState* _state;
	public:
		DX11SamplerState(GEGraphics* engine,SamplerFilter filter = SamplerFilter::Anisotropic);

		void bind() override;
	};
}
