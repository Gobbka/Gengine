#pragma once
#include <d3d11.h>
#include "../Common/GraphicsCommon.h"

namespace Render
{
	struct __declspec(dllexport) VBufferDesc {
		enum class Usage
		{
			classic,
			immutable,
			dynamic
		}   usage = Usage::classic;
		size_t length = 0;
		size_t stride_size;
		void* p_data = nullptr;
	};

	class __declspec(dllexport) DX11VBuffer
	{
		GEGraphics* _graphics;
		ID3D11Buffer* _buffer;
	protected:
		VBufferDesc desc;
	public:
		DX11VBuffer(GEGraphics* graphics, VBufferDesc);
		DX11VBuffer(DX11VBuffer& copy);
		DX11VBuffer(DX11VBuffer&& move) noexcept;
		~DX11VBuffer();

		void bind() const;
		void update(UINT update_size = -1) const;

		void copyTo(DX11VBuffer* buffer) const;
		void copyTo(void* buffer, UINT size) const;

		size_t getLength() const;
	};
}
