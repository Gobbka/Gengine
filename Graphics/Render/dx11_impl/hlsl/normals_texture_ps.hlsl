struct PSI
{
	float4 viewPos : SV_POSITION;
	float3 worldPos : Position;
	float3 texCoord : COLOR;
	float3 normal : NORMAL;
	float3 tangent: TANGENT;
};

Texture2D normals : register(t0);
SamplerState objSamplerState : SAMPLER: register(s0);

float4 main(PSI psi) : SV_TARGET
{
	float3 tangent_space_normal_packed = normals.Sample(objSamplerState,psi.texCoord);
	float3 tangent_space_normal = tangent_space_normal_packed * 2 - 1.f;

	const float3 tangent = psi.tangent;
	const float3 bitangent = cross(tangent,psi.normal);

	const float3x3 trans_matrix = {
		tangent.x, bitangent.x, psi.normal.x,
		tangent.y, bitangent.y, psi.normal.y,
		tangent.z, bitangent.z, psi.normal.z,
	};

	float3 worldSpaceNormal = mul(tangent_space_normal, trans_matrix);
	float3 worldSpaceNormal_packed = mul(worldSpaceNormal, 0.5) + 0.5;

	return float4(worldSpaceNormal_packed,1.f);
}