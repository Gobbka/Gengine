#pragma once
#include "../Bindable.h"

#include "../../../Graphics.h"
#include <cassert>
#include <d3d11.h>


namespace Render {

	enum CBBindFlag : BYTE
	{
		CBBindFlag_vs = 0x1,
		CBBindFlag_ps = 0x2,
	};
	
	template<typename T>
	class __declspec(dllexport) ConstantBuffer : Render::Bindable
	{
		ID3D11Buffer* _d3d_buffer;
		UINT _slot = 0;
		BYTE _binds = 0;
	public:
		T data;
		
		ConstantBuffer(Core::GraphicsContext*engine, UINT slot = 0,BYTE binds = CBBindFlag_vs);

		void update() const;
		void bind() override;
	};

	template <typename T>
	ConstantBuffer<T>::ConstantBuffer(Core::GraphicsContext* engine, UINT slot, BYTE binds)
			: Bindable(engine)
	{
		_binds = binds;
		_slot = slot;

		D3D11_BUFFER_DESC desc{ sizeof(T),D3D11_USAGE_DEFAULT,D3D11_BIND_CONSTANT_BUFFER,0,0,0 };
		D3D11_SUBRESOURCE_DATA sd{ &data,0,0 };

		auto hr = _engine->device->CreateBuffer(&desc, &sd, &_d3d_buffer);
		assert(SUCCEEDED(hr));
	}

	template <typename T>
	void ConstantBuffer<T>::update() const
	{
		_engine->context->UpdateSubresource(_d3d_buffer, 0, nullptr, &data, 0, 0);
	}

	template <typename T>
	void ConstantBuffer<T>::bind()
	{
		if (_binds & CBBindFlag_vs)
			_engine->context->VSSetConstantBuffers(_slot, 1, &_d3d_buffer);

		if (_binds & CBBindFlag_ps)
			_engine->context->PSSetConstantBuffers(_slot, 1, &_d3d_buffer);
	}
}
