//cbuffer ConstantBuffer2D : register(b0)
//{
//	float alpha;
//}

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
	psi.pos.x = pos.x / 400.f;
	psi.pos.y = pos.y / 300.f;
	return psi;
}
