#pragma once

namespace Core {
	class GraphicsContext;
}

namespace Render
{
	typedef Core::GraphicsContext* IStepVTableArgument;
	
	struct IStepVTable
	{
		virtual ~IStepVTable() = default;
		
		virtual void disable_ps(IStepVTableArgument context) =0;
	};
}
