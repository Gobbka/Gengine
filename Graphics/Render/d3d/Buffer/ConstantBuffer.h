#pragma once
#include "../Bindable.h"
#include <d3d11.h>

namespace Render {

	class ConstantBuffer : Render::Bindable
	{
		ID3D11Buffer* _d3d_buffer;
		void* _struct;
		UINT _slot = 0;
	public:
		ConstantBuffer(D3DEngine*engine,void* struct_pointer,UINT struct_size, UINT slot = 0);

		void update() const;
		void bind() override;
	};
}
