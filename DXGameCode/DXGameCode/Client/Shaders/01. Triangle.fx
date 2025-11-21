
struct VertexInput
{
	float4 position : POSITION;
};
//VS의 입력데이터. Position을 4차원으로 정의. (CPU -> GPU)
struct VertexOutput
{
	float4 position : SV_POSITION;
};
//PS로 보내기 위한 입력데이터. RS로 보내기 위해 SV(Semantic) 형태다.
VertexOutput VS(VertexInput input)
{
	VertexOutput output;
	output.position = input.position;

	return output;
}
//output=input에서 볼 수 있듯이, MVP행렬을 이때 변환하고 output으로 던져준다.
float4 PS(VertexOutput input) : SV_TARGET
{
	return float4(1, 0, 0, 1);
}//PS단계이며 RenderTarget 즉, 백버퍼로 기록될 타겟이다의 색상이다.
float4 PS2(VertexOutput input) : SV_TARGET
{
	return float4(0, 1, 0, 1);
}//

float4 PS3(VertexOutput input) : SV_TARGET
{
	return float4(0, 0, 1, 1);
}

technique11 T0
{//효과나 렌더링 방식을 구현하기 위한 State, Shader의 조합.
	pass P0
	{//Technique의 산하로, 셰이더 세트를 의미한다.
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P1
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS2()));
	}
};

technique11 T1
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS3()));
	}
};