#include "D3D11StepVTable.h"

#include "../../Graphics.h"

void Render::D3D11StepVTable::disable_ps(IStepVTableArgument context)
{
	context->context->PSSetShader(nullptr, nullptr, 0);
}
