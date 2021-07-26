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
	float4 color : COLOR;
};

// VertexShader
PSI VS(float4 pos : POSITION, float4 color : COLOR)
{
	PSI psi;
	psi.color = color;
	psi.color.a = c_opacity;

	psi.pos = mul(float4(pos.x, pos.y, pos.z, 1.f), viewMatrix);
	psi.pos.x += c_offset.x;
	psi.pos.y += c_offset.y;

	return psi;
}
