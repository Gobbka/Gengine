#include "SamplerState.h"
#include "../../Engine/D3DEngine.h"

Render::SamplerState::SamplerState(D3DEngine* engine)
	: Bindable(engine)
{
	D3D11_SAMPLER_DESC desc{};
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	desc.MinLOD = 0;
	
	assert(SUCCEEDED(_engine->device()->CreateSamplerState(&desc, &_state)));
}

void Render::SamplerState::bind()
{
	_engine->context()->PSSetSamplers(0, 1, &_state);
}
