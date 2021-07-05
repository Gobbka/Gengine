struct PSI
{
	float4 pos : SV_POSITION;
	float4 color : COLOR;
};

// PixelShader
float4 PS(PSI psi) : SV_TARGET
{
	return psi.color;
}