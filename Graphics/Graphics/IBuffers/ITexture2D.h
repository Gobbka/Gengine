#pragma once

namespace Render
{
	struct ITexture2DDesc
	{
		DXGI_FORMAT format;
		UINT32 width;
		UINT32 height;

		UINT32 stride;
		UINT32 rows;

		void* pSysMem;
	};

	class ITexture2D
	{
	public:
		virtual unsigned width() PURE;
		virtual unsigned height() PURE;
		
		virtual char* get_data(size_t* lpsize = nullptr) PURE;

		virtual bool is_render_target() PURE;
		virtual bool is_shader_resource() PURE;

		virtual void bind() PURE;
	};
}
