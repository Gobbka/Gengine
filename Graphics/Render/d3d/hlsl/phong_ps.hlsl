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

static const float3 lightpos = {-1,-1,-1};
static const float pointLightIntensity = 7.f;

static const float3 ambientLightColor = { 1.f,1.f,1.f };
static const float ambientLightIntensity = 0.3f;

float4 main(PSI input) : SV_TARGET
{
	float4 pixelColor = objTexture.Sample(objSamplerState,input.texCoord);

	float3 ambientLight = ambientLightIntensity * ambientLightColor;

	float3 appliedLight = ambientLight;

	float3 vectorToLight = normalize(lightpos - input.worldPos);
	float3 diffuseLightIntensity = max(dot(vectorToLight, input.normal), 0.f);
	float3 diffuseLight = diffuseLightIntensity;
	appliedLight += diffuseLight * max(pointLightIntensity - length(lightpos - input.worldPos),0);
	float3 finalColor = pixelColor * appliedLight;

	return float4(finalColor, 1.f);
}