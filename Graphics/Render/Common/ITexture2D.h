#pragma once
#include <d3d11.h>

namespace Render
{
	struct ITexture2DDesc
	{
		enum class Usage
		{
			DEFAULT,
			STAGING
		} usage;

		UINT bind_flag;
		DXGI_FORMAT format;
		UINT32 width;
		UINT32 height;

		UINT32 stride;
		UINT32 rows;

		void* pSysMem;

		ITexture2DDesc(
			Usage usage,
			UINT bind_flag,
			DXGI_FORMAT format,
			UINT32 width,
			UINT32 height,
			UINT32 stride,
			UINT32 rows,
			void* pSysMem
		)
			: usage(usage)
			, bind_flag(bind_flag)
			, format(format)
			, width(width)
			, height(height)
			, stride(stride)
			, rows(rows)
			, pSysMem(pSysMem)
		{}

		ITexture2DDesc()
			: usage(Usage::DEFAULT)
			, bind_flag(D3D11_BIND_SHADER_RESOURCE)
			, format(DXGI_FORMAT_UNKNOWN)
			, width(0)
			, height(0)
			, stride(0)
			, rows(0)
			, pSysMem(nullptr)
		{}
	};

	class ITexture2D
	{
	public:
		virtual ~ITexture2D() = default;
		virtual unsigned width() PURE;
		virtual unsigned height() PURE;
		
		virtual char* get_data(size_t* lpsize = nullptr) PURE;

		virtual bool is_render_target() PURE;
		virtual bool is_shader_resource() PURE;

		virtual void bind(UINT slot=0) PURE;
	};
}
