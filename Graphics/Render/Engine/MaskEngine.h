#pragma once
#include <d3d11.h>

#include "../d3d/Bindable.h"


struct Surface;

namespace Render {
	class RenderTarget;
	class WorldViewer;

	enum class StencilUsage : __int8
	{
		normal,
		write,
		mask,
	};
	
	class __declspec(dllexport) Stencil
	{
		ID3D11DeviceContext* _context;
		ID3D11DepthStencilState* _state;
	public:
		Stencil(Core::GraphicsContext* context, StencilUsage usage);

		void bind(UINT reference = 0) const;

		~Stencil();
	};

	enum class MaskEngineUsage
	{
		Depth,
		DepthStencil,
	};
	
	class __declspec(dllexport) MaskEngine : public Bindable
	{
	private:
		Stencil _disabledState;
		Stencil _drawState;
		Stencil _discardState;
		Stencil* _currentState;

		ID3D11Texture2D* _buffer;
		ID3D11DepthStencilView* _view;
		RenderTarget* _target;
	public:
		MaskEngine(WorldViewer* target, MaskEngineUsage usage = MaskEngineUsage::DepthStencil,Surface* resolution=nullptr);

		void set_state(Stencil* state,UINT reference = 0,bool force = false);
		void clear_buffer() const;
		
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
