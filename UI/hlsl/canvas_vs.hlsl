cbuffer cb0 : register(b0)
{
	float4x4 mvp;
}

struct PSI
{
	float4 sv_pos : SV_POSITION;
	float3 color : COLOR;
	float2 uv : UV;
};

PSI main(float2 pos : POSITION, float3 color : COLOR, float2 uv : UV)
{
	PSI psi;
	psi.sv_pos = mul(pos, mvp);
	psi.color = color;
	psi.uv = uv;
	
	return psi;
}