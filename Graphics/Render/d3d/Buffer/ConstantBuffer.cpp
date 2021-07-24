#include "ConstantBuffer.h"
#include "../../Engine/Camera.h"


Render::ConstantBuffer::ConstantBuffer(Core::GraphicsContext* engine, void* struct_pointer, UINT struct_size, UINT slot )
	: Bindable(engine)
{
	_struct = struct_pointer;
	_slot = slot;

	D3D11_BUFFER_DESC desc{ struct_size,D3D11_USAGE_DEFAULT,D3D11_BIND_CONSTANT_BUFFER,0,0,0 };
	D3D11_SUBRESOURCE_DATA sd{ _struct,0,0 };

	auto hr = _engine->device->CreateBuffer(&desc, &sd, &_d3d_buffer);
	assert(SUCCEEDED(hr));
}

void Render::ConstantBuffer::update() const
{
	_engine->context->UpdateSubresource(_d3d_buffer, 0, nullptr, _struct, 0, 0);
}

void Render::ConstantBuffer::bind()
{
	_engine->context->VSSetConstantBuffers(_slot, 1, &_d3d_buffer);
}
