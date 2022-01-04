// PSI (PixelShaderInput)
struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

Texture2D objTexture : TEXTURE: register(t0);
Texture2D normalsTexture : TEXTURE: register(t1);
SamplerState objSamplerState : SAMPLER: register(s0);

static const float3 lightpos = {9,0,9};
static const float pointLightIntensity = 9.f;

static const float3 ambientLightColor = { 1.f,1.f,1.f };
static const float ambientLightIntensity = 0.1f;

float4 main(PSI input) : SV_TARGET
{
	float4 texColor = objTexture.Sample(objSamplerState,input.texCoord);

	float3 ambientLight = ambientLightIntensity * ambientLightColor;

	float3 appliedLight = ambientLight;

	const float3 vectorToLight = lightpos - input.worldPos;
	const float3 vectorToLLength = length(vectorToLight);
	const float3 normalizedVector = vectorToLight / vectorToLLength;
	if(dot(normalizedVector,input.normal)>0)
	{
		float ntWidth;
		float ntHeight;
		normalsTexture.GetDimensions(ntWidth, ntHeight);
		float3 normal = normalsTexture.Sample(objSamplerState, float2(input.viewPos.x / ntWidth, input.viewPos.y / ntHeight));
		normal = normal * 2 - 1;

		float3 diffuseLight = max(dot(normalizedVector, normal), 0) * max(pointLightIntensity-vectorToLLength,0);
		appliedLight += diffuseLight;
	}


	float3 finalColor = texColor * appliedLight;

	return float4(finalColor, 1.f);
}