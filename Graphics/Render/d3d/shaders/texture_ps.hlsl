cbuffer ConstantBuffer2D : register(b0)
{
	float width;
	float height;
	float c_alpha;
}

// PSI (PixelShaderInput)
struct PSI
{
	float4 pos : SV_POSITION;
	float2 texCoord : TEXCOORD;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

float4 main(PSI input) : SV_TARGET
{
	float3 pixelColor = objTexture.Sample(objSamplerState,input.texCoord);
	return float4(pixelColor, 1.0f);
}