cbuffer ConstantBuffer2D : register(b0)
{
	float4x4 ModelViewProjectionMatrix;
	float4x4 ModelMatrix;
}

cbuffer ControlBuffer : register(b1)
{
	float c_opacity;
}

// PSI (PixelShaderInput)
struct PSI
{
	float4 pos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
};

// VertexShader
PSI VS(float3 pos : POSITION, float3 texcoord : COLOR, float3 normal : NORMAL)
{
	PSI psi;
	psi.texCoord = texcoord;
	psi.pos = mul(float4(pos, 1.f), ModelViewProjectionMatrix);
	psi.worldPos = mul(float4(pos,1.f),ModelMatrix);
	psi.normal = normal;
	
	return psi;
}