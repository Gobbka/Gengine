#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"


namespace Render {
	class MaskEngine : Bindable
	{
	private:
		ID3D11DepthStencilState* _disabledState;
		ID3D11DepthStencilState* _drawState;
		ID3D11DepthStencilState* _discardState;
		ID3D11DepthStencilState* _currentState;

		ID3D11Texture2D* _buffer;
		ID3D11DepthStencilView* _view;
	public:
		MaskEngine(Render::Camera* target);

		void set_state(ID3D11DepthStencilState* state,UINT reference = 0);
		void set_state_force(ID3D11DepthStencilState* state,UINT reference = 0);
		void clear_buffer();
		
		void bind() override;

		auto get_view() { return _view; }

		ID3D11DepthStencilState* get_drawState() CONST
		{
			return _drawState;
		}
		ID3D11DepthStencilState* get_discardState() CONST
		{
			return _discardState;
		}
		ID3D11DepthStencilState* get_disabledState() CONST
		{
			return _disabledState;
		}

		ID3D11DepthStencilState* get_current_state() CONST
		{
			return _currentState;
		}
	};
}
