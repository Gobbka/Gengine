SamplerState sample : register(s0);
Texture2D objTexture : register(t0);

struct PSI
{
	float4 sv_pos : SV_POSITION;
	float3 color : COLOR;
	float2 uv : UV;
};

float4 main(PSI psi) : SV_TARGET
{
	float3 final_color = psi.color * objTexture.Sample(sample,psi.uv);
	return float4(final_color,1);
}