#pragma once
#include <vector>

#include "../../Graphics.h"
#include "../Layer/ILayer.h"

namespace Render
{
	class D3DEngine
	{
	private:
		Core::GraphicsContext* _context;
	public:
		bool create_buffer(D3D11_BUFFER_DESC* desc,D3D11_SUBRESOURCE_DATA*data,ID3D11Buffer**buffer) const;
		
	public:
		ID3D11DeviceContext* context() const;
	public:
		
		D3DEngine(Core::GraphicsContext* context);

		void present(DrawEvent* event);
	};
}
