#pragma once
#include "../SpriteFont.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class IIndexBuffer;
	class IVertexBuffer;
	class IGDevice;

	struct __declspec(dllexport) TextComponent
	{
	private:
		wchar_t* _text;
		IGDevice* _device;
	public:
		SpriteFont* font;
		IVertexBuffer* vbuffer;
		IIndexBuffer* ibuffer;

		TextComponent(Core::GraphicsContext* context,SpriteFont* font);
		TextComponent(TextComponent&& other) noexcept;
		TextComponent& operator=(TextComponent&& other) noexcept;
		~TextComponent();

		void set_text(const wchar_t* text);
	};
}
