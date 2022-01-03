#include "SamplerState.h"

#include "../../../Graphics.h"
#include "Logger/Logger.h"

D3D11_FILTER SamplerFilterToD3D11Filter(Render::SamplerFilter filter)
{
	switch (filter)
	{
	case Render::SamplerFilter::MinMagMip:
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	case Render::SamplerFilter::Anisotropic:
		return D3D11_FILTER_ANISOTROPIC;
	default:
		return D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	}
}

Render::SamplerState::SamplerState(Core::GraphicsContext* engine, SamplerFilter filter)
	: Bindable(engine)
	, _state(nullptr)
{

	D3D11_SAMPLER_DESC desc{};
	desc.Filter = SamplerFilterToD3D11Filter(filter);
	desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	desc.MaxLOD = D3D11_FLOAT32_MAX;
	desc.MinLOD = 0;

	GEAssert(_engine->device->CreateSamplerState(&desc, &_state))
		.abort(TEXT("SamplerState.cpp: Cannot create sampler state"));
}

void Render::SamplerState::bind()
{
	_engine->context->PSSetSamplers(0, 1, &_state);
}
