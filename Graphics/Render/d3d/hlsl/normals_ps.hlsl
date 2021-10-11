struct PSI
{
	float4 pos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
};

float4 main(PSI psi) : SV_TARGET
{
	return float4(psi.normal, 1.0f);
}