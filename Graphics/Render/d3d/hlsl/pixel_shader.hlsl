struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

cbuffer ControlBuffer : register(b1)
{
	float c_opacity;
}

// PixelShader
float4 PS(PSI psi) : SV_TARGET
{
	return float4(psi.texCoord,c_opacity);
}