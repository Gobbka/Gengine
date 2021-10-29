struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
};

Texture2D normals : register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

float4 main(PSI psi) : SV_TARGET
{
	// TODO: convert to tangent space
	float3 normal = normals.Sample(objSamplerState,psi.texCoord);
	const float cosine = dot(float3(0,0,1), psi.normal);
	const float sine = cross(float3(0,0,1),psi.normal);
	
	float3x3 rotation_matrix;

	rotation_matrix[0] = float3(cosine, 0 ,  sine );
	rotation_matrix[1] = float3(  0   , 1 ,   0   );
	rotation_matrix[2] = float3(-sine , 0 , cosine);

	return float4(mul(normal,rotation_matrix),1.f);
}