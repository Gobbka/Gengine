#include "D3DEngine.h"

#include <iostream>

#include "../../Graphics/Types.h"
#include "BlendEngine.h"
#include "MaskEngine.h"

bool Render::D3DEngine::create_buffer(D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data, ID3D11Buffer** buffer) const
{
	return SUCCEEDED(_context->device()->CreateBuffer(desc, data, buffer));
}

void Render::D3DEngine::set_resolution(Surface new_resolution)
{
	std::cout << "NEW RESOLUTION: " << new_resolution.width << " " << new_resolution.height << '\n';
	_b0_constant_buffer_struct.width = new_resolution.width;
	_b0_constant_buffer_struct.height = new_resolution.height;
	b0_buffer->update();
}

void Render::D3DEngine::set_alpha(float alpha)
{
	_b0_constant_buffer_struct.alpha = alpha;
	b0_buffer->update();
}

ID3D11DeviceContext* Render::D3DEngine::context() const
{
	return _context->context();
}

ID3D11Device* Render::D3DEngine::device() const
{
	return _context->device();
}

ID3D11RenderTargetView* Render::D3DEngine::get_target_view() const
{
	return _context->get_render_target_view();
}

Render::MaskEngine* Render::D3DEngine::mask_engine() const
{
	return _maskEngine;
}

Render::BlendEngine* Render::D3DEngine::blend_engine() const
{
	return _blendEngine;
}

Surface Render::D3DEngine::get_screen_resolution() const
{
	return _context->get_screen_resolution();
}

Render::D3DEngine::D3DEngine(Core::GraphicsContext* context)
{
	_context = context;
	_blendEngine = new BlendEngine(this);
	_maskEngine  = new MaskEngine(this);
	
	_b0_constant_buffer_struct = { 800,600,0.5 };

	b0_buffer = new ConstantBuffer(this, &_b0_constant_buffer_struct, sizeof(_b0_constant_buffer_struct), 0);
	b0_buffer->update();

}

void Render::D3DEngine::present(DrawEvent* event)
{
	_blendEngine->bind();
	b0_buffer->bind();
	//_maskEngine->bind();
	
	event->layer->render(event);
}
