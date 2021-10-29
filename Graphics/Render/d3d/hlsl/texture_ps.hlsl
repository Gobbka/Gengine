// PSI (PixelShaderInput)
struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

float4 main(PSI input) : SV_TARGET
{
	float4 pixelColor = objTexture.Sample(objSamplerState,input.texCoord);
	return pixelColor;
}