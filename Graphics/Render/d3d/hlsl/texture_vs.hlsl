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
	psi.worldPos = mul(float4(pos,1.f),ModelMatrix).xyz;
	
	MATRIX model_matrix = ModelMatrix; // model matrix without translation
	model_matrix[0].w = 0;
	model_matrix[1].w = 0;
	model_matrix[2].w = 0;

	psi.normal = mul(normal,ModelMatrix);
	
	return psi;
}