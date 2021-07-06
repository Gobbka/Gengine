
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
	psi.pos = pos;
	psi.pos.x = pos.x / (width / 2) -1;
	psi.pos.y = pos.y / (height / 2) +1;
	return psi;
}
