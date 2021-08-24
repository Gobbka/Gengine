// PSI (PixelShaderInput)
struct PSI
{
	float4 pos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
};

Texture2D objTexture : TEXTURE: register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

static const float3 lightpos = {0,0,0};

// dynamic light code =======
// float4 pixelColor = objTexture.Sample(objSamplerState, input.texCoord);
// float distToL = length(lightpos - input.worldPos);
// 
// float lightTaken = 1.f - distToL * .5f;
// float satured = saturate(lightTaken);
// return float4((float3)pixelColor * satured, 1.f);

float4 main(PSI input) : SV_TARGET
{
	float4 pixelColor = objTexture.Sample(objSamplerState,input.texCoord);
	return pixelColor;
}