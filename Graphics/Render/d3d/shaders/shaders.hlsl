
cbuffer ConstantBuffer2D : register(b0)
{
	float width;
	float height;
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
	psi.color.a = 0.0f;

	psi.pos = float4(
		pos.x / (width / 2.f)  - 1, 
		pos.y / (height / 2.f) + 1,
		1.f, 
		1.f
	);

	return psi;
}
