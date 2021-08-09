#pragma once
#include "../Bindable.h"
#include <d3d11.h>

namespace Render {

	class ConstantBuffer : Render::Bindable
	{
	public:
		enum CBBindFlag : BYTE
		{
			CBBindFlag_vs = 0x1,
			CBBindFlag_ps = 0x2,
		};
		
	private:
		ID3D11Buffer* _d3d_buffer;
		void* _struct;
		UINT _slot = 0;
		BYTE _binds = 0;
	public:
		
		ConstantBuffer(Core::GraphicsContext*engine,void* struct_pointer,UINT struct_size, UINT slot = 0,BYTE binds = CBBindFlag_vs);

		void update() const;
		void bind() override;
	};
}
