struct PSI
{
	float4 pos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
};

cbuffer ControlBuffer : register(b1)
{
	float2 c_offset;
	float c_opacity;
}

// PixelShader
float4 PS(PSI psi) : SV_TARGET
{
	return float4(psi.texCoord,c_opacity);
}