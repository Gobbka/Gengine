#pragma once

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	class IIndexBuffer;
	class IVertexBuffer;
	class IGDevice;
	struct SpriteFont;

	struct __declspec(dllexport) TextComponent
	{
	private:
		wchar_t* _text;
		IGDevice* _device;
	public:
		SpriteFont* font;
		IVertexBuffer* vbuffer;
		IIndexBuffer* ibuffer;

		TextComponent(Core::GraphicsContext* context);
		~TextComponent();

		void set_text(wchar_t* text);
	};
}
