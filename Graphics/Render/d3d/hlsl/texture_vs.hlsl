cbuffer ConstantBuffer2D : register(b0)
{
	float4x4 viewMatrix;
}

cbuffer ControlBuffer : register(b1)
{
	float2 c_offset;
	float c_opacity;
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
	psi.pos.x += c_offset.x;
	psi.pos.y += c_offset.y;
	
	return psi;
}