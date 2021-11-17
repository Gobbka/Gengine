SamplerState sample : register(s0);
Texture2D objTexture : register(t0);

struct PSI
{
	float4 sv_pos : SV_POSITION;
	float3 color : COLOR;
	float2 uv : UV;
};

cbuffer ControlBuffer : register(b1)
{
	float c_opacity;
}

float4 main(PSI psi) : SV_TARGET
{
	float3 final_color = psi.color * objTexture.Sample(sample,psi.uv) * c_opacity;
	return float4(final_color,1);
}