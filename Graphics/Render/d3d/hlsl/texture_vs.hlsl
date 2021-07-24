cbuffer ConstantBuffer2D : register(b0)
{
	float4x4 viewMatrix;
}

// PSI (PixelShaderInput)
struct PSI
{
	float4 pos : SV_POSITION;
	float3 texCoord : TEXCOORD;
};

// VertexShader
PSI VS(float4 pos : POSITION, float3 texcoord : TEXCOORD)
{
	PSI psi;
	psi.texCoord = texcoord;
	psi.pos = mul(float4(pos.x, pos.y, pos.z, 1.f), viewMatrix);
	
	return psi;
}