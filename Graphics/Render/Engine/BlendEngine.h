#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"

namespace Render
{
	class BlendEngine final : Bindable
	{
	private:
		ID3D11BlendState* _blend;
	public:
		BlendEngine(Core::GraphicsContext* engine);
		
		void bind() override;
	};
}
