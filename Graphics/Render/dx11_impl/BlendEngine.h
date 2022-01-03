#pragma once
#include <d3d11.h>
#include "../Common/IBlendEngine.h"

namespace Render
{
	class BlendEngine final : public IBlendEngine
	{
		ID3D11BlendState* _blend;
	public:
		BlendEngine(Core::GraphicsContext* engine);
		
		void bind() override;
	};
}
