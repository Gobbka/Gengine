#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"


namespace Render {

	enum class StencilUsage
	{
		normal,
		write,
		mask,
	};
	
	class Stencil
	{
		ID3D11DeviceContext* _context;
		ID3D11DepthStencilState* _state;
	public:
		Stencil(Core::GraphicsContext* context, StencilUsage usage);

		void bind(UINT reference = 0);

		~Stencil();
	};
	
	class MaskEngine : public Bindable
	{
	private:
		Stencil _disabledState;
		Stencil _drawState;
		Stencil _discardState;
		Stencil* _currentState;

		ID3D11Texture2D* _buffer;
		ID3D11DepthStencilView* _view;
	public:
		MaskEngine(Render::Camera* target);

		void set_state(Stencil* state,UINT reference = 0);
		void clear_buffer();
		
		void bind() override;

		auto get_view() { return _view; }

		auto* get_drawState() 
		{
			return &_drawState;
		}
		auto* get_discardState() 
		{
			return &_discardState;
		}
		auto* get_disabledState()
		{
			return &_disabledState;
		}

		auto* get_current_state() CONST
		{
			return _currentState;
		}
	};
}
