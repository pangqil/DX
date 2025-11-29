#include "00. Global.fx"

float3 LightDir;
float4 LightDiffuse;
float4 MaterialDiffuse;
Texture2D DiffuseMap;

VertexOutput VS(VertexTextureNormal input)
{
	VertexOutput output;
	output.position = mul(input.position, W);
	output.position = mul(output.position, VP);
	output.uv = input.uv;
	output.normal = mul(input.normal, (float3x3)W);

	return output;
}

// Diffuse (분산광)
// 빛이 물체에 부딪혀서 내는 음영. 
// 각도에 따라 밝기가 다르다 (Lambert 공식)
float4 PS(VertexOutput input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	
	float value = dot(-LightDir, normalize(input.normal));
	color = color * value * LightDiffuse * MaterialDiffuse;

	return color;
}

technique11 T0
{
	PASS_VP(P0, VS, PS)
};
