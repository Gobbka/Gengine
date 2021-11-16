#pragma once
#include "../SpriteFont.h"

namespace Core
{
	class GraphicsContext;
}

namespace Render
{
	struct Vertex;
	class IIndexBuffer;
	template<typename T>
	class IVertexBuffer;
	class IGDevice;

	struct __declspec(dllexport) TextComponent
	{
	private:
		wchar_t* _text;
		IGDevice* _device;
	public:
		SpriteFont* font;
		IVertexBuffer<Vertex>* vbuffer;
		IIndexBuffer* ibuffer;

		TextComponent(Core::GraphicsContext* context,SpriteFont* font);
		TextComponent(TextComponent&& other) noexcept;
		TextComponent& operator=(TextComponent&& other) noexcept;
		~TextComponent();

		void set_text(const wchar_t* text);
	};
}
