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

static const float3 lightpos = {0,2.5,0};
static const float3 ambientLightColor = { 1.f,1.f,1.f };
static const float ambientLightIntensity = 0.3f;

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

	float3 ambientLight = ambientLightIntensity * ambientLightColor;

	float3 appliedLight = ambientLight;

	float3 vectorToLight = normalize(lightpos - input.worldPos);
	float3 diffuseLightIntensity = max(dot(vectorToLight, input.normal), 0.f);
	float3 diffuseLight = diffuseLightIntensity * .5f;
	appliedLight += diffuseLight;
	float3 finalColor = pixelColor * appliedLight;
	//float distToL = distance(lightpos, input.worldPos);
	// 
	//float lightTaken = 1.f - distToL * .3f;
	//float satured = saturate(lightTaken) + 0.2f;
	return float4(finalColor, 1.f);
}