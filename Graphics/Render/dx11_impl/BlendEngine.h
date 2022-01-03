#pragma once
#include <d3d11.h>
#include "../Common/Bindable.h"

namespace Render
{
	class DX11BlendEngine final : public Bindable
	{
		ID3D11BlendState* _blend;
	public:
		DX11BlendEngine(Core::GraphicsContext* engine);
		
		void bind() override;
	};
}
