cbuffer ConstantBuffer2D : register(b0)
{
	float width;
	float height;
	float c_alpha;
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
	psi.pos = float4(
		pos.x / (width / 2.f) - 1,
		pos.y / (height / 2.f) + 1,
		1.f,
		1.f
		);

	return psi;
}