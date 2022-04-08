#pragma once
#include <d3d11.h>
#include "../Common/GraphicsCommon.h"

namespace Render
{
	enum CBBindFlag : unsigned char
	{
		CBBindFlag_vs = 0x1,
		CBBindFlag_ps = 0x2,
	};

	class __declspec(dllexport) DX11ConstantBuffer
	{
		GEGraphics* _gfx;
		ID3D11Buffer* _d3d_buffer;
		UINT _slot = 0;
		BYTE _binds = 0;
		void* _data;
	public:
		DX11ConstantBuffer(GEGraphics* gfx,UINT data_size,UINT slot,BYTE binds = CBBindFlag_vs);
		void update() const;
		void bind() const;

		void* data() const;
	};

	template<typename T>
	class ConstantBuffer : public GEConstantBuffer
	{
	public:
		ConstantBuffer(GEGraphics* gfx, unsigned slot, unsigned char binds = CBBindFlag_vs)
			: GEConstantBuffer(gfx, sizeof(T), slot, binds)
		{
		}

		T* data()
		{
			return (T*)GEConstantBuffer::data();
		}
	};
}
