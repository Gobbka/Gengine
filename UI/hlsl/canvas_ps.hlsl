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
	float4 final_color = float4(psi.color,1.f) * objTexture.Sample(sample,psi.uv);
	return final_color;
}