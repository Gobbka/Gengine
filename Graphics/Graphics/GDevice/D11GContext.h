#pragma once
#include "../../IGContext.h"

namespace Render {
	class D11GContext final : public Render::IGContext
	{
		ID3D11DeviceContext* _d11context;
	public:
		D11GContext(Core::GraphicsContext* context,ID3D11DeviceContext*d11context);
	};
}