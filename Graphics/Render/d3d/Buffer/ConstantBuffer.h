#pragma once
#include <d3d11.h>
#include "../../../Graphics.h"
#include "Logger/Logger.h"

namespace Render
{
	enum CBBindFlag : BYTE
	{
		CBBindFlag_vs = 0x1,
		CBBindFlag_ps = 0x2,
	};

	template<typename T>
	class __declspec(dllexport) ConstantBuffer
	{
		GEGraphics* _context;
		ID3D11Buffer* _d3d_buffer;
		UINT _slot = 0;
		BYTE _binds = 0;
	public:
		T data;

		ConstantBuffer(GEGraphics* engine, UINT slot = 0, BYTE binds = CBBindFlag_vs);

		void update() const;
		void bind();
	};

	template <typename T>
	ConstantBuffer<T>::ConstantBuffer(GEGraphics* engine, UINT slot, BYTE binds)
		: _context(engine)
		, _d3d_buffer(nullptr)
		, _slot(slot)
		, _binds(binds)
	{
		D3D11_BUFFER_DESC desc{ sizeof(T),D3D11_USAGE_DEFAULT,D3D11_BIND_CONSTANT_BUFFER,0,0,0 };
		D3D11_SUBRESOURCE_DATA sd{ &data,0,0 };

		GEAssert(_context->device->CreateBuffer(&desc, &sd, &_d3d_buffer))
			.abort(TEXT("ConstantBuffer.cpp: cannot create constant buffer"));
	}

	template <typename T>
	void ConstantBuffer<T>::update() const
	{
		_context->context->UpdateSubresource(_d3d_buffer, 0, nullptr, &data, 0, 0);
	}

	template <typename T>
	void ConstantBuffer<T>::bind()
	{
		if (_binds & CBBindFlag_vs)
			_context->context->VSSetConstantBuffers(_slot, 1, &_d3d_buffer);

		if (_binds & CBBindFlag_ps)
			_context->context->PSSetConstantBuffers(_slot, 1, &_d3d_buffer);
	}
}
