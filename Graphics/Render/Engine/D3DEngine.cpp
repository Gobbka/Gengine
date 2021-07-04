#include "D3DEngine.h"

bool Render::D3DEngine::create_buffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer) const
{
	return SUCCEEDED(_context->device()->CreateBuffer(desc, data, buffer));
}

ID3D11DeviceContext* Render::D3DEngine::context() const
{
	return _context->context();
}

Render::D3DEngine::D3DEngine(Core::GraphicsContext* context)
{
	_context = context;
}

void Render::D3DEngine::present(DrawEvent* event)
{
	for(auto*layer:_layers)
	{
		layer->render(event);
	}
}
