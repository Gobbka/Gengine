
cbuffer ConstantBuffer2D : register(b0)
{
	float4x4 view_matrix;
	float c_alpha;
}

// PSI (PixelShaderInput)
struct PSI
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

// VertexShader
PSI VS(float4 pos : POSITION, float4 color : COLOR)
{
	PSI psi;
	psi.color = color;
	psi.color.a = c_alpha;

	psi.pos = mul(float4(pos.x, pos.y, pos.z, 1.f), view_matrix);
	psi.pos.x -= 1.f;
	psi.pos.y += 1.f;

	return psi;
}
