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
	psi.pos = pos;

	return psi;
}