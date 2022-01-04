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
		DX11SamplerState(Core::GraphicsContext* engine,SamplerFilter filter = SamplerFilter::Anisotropic);

		void bind() override;
	};
}
