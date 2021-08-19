#pragma once
#include "IStepVTable.h"
#include "Step.h"

namespace Render {
	struct D3D11StepVTable : IStepVTable
	{
		void disable_ps(IStepVTableArgument context) override;
	};
}
