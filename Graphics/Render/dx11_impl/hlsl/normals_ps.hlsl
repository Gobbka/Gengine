struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

float4 main(PSI psi) : SV_TARGET
{
	return float4(mul(psi.normal,0.5f) + 0.5f, 1.0f);
}