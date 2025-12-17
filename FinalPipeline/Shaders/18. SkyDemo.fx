#include "00. Global.fx"
#include "00. Light.fx"

struct VS_OUT
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOORD;
};

VS_OUT VS(VertexTextureNormalTangent input)
{
	VS_OUT output;

	// Local -> World -> View -> Projection
	//여기서 MVP중 M을 World로 변환하지 않는 이유는 어차피 로컬만 알면 되기 때문이며, 0을 통해 회전만 적용시킴
	float4 viewPos = mul(float4(input.position.xyz, 0), V);
	float4 clipSpacePos = mul(viewPos, P);
	output.position = clipSpacePos.xyzw;
	output.position.z = output.position.w * 0.999999f;
    //0.99인 이유는 D3D11_COMPARISON_LESS_EQUAL에 따라 1보다 작으면 렌더링 하지 않음.
	output.uv = input.uv;

	return output;
}
//ViewSpace의 Z축은 항상 카메라의 LookVector다. 즉 Z는 오브젝트와 카메라 거리. 
// V-> Projection 변환을 하는 과정에 두 행렬의 곱 뿐만 아니라 Z를 W에 저장한다
//P행렬을 곱하면서, W가 단순히 0과 1이 아닌, 깊이정보(-Z)로 변한다.
//MVP를 통해 투영변환을 하면 Clipspace가 나온다. 이를 w로 나누면 비로소 NDC가 되는것이다.
float4 PS(VS_OUT input) : SV_TARGET
{
	float4 color = DiffuseMap.Sample(LinearSampler, input.uv);
	return color;
}

technique11 T0
{
	pass P0
	{
		SetRasterizerState(FrontCounterClockwiseTrue);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};
