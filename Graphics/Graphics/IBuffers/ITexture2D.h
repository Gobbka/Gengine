#pragma once

namespace Render
{
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
