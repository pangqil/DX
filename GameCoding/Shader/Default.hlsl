
struct VS_INPUT
{
	float4 position : POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};
//vs는 position과 uv를 활용해서 mvp변환을 하고, 이를 svposition으로 바꾼다.
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	//float4 color : COLOR;
	float2 uv : TEXCOORD;
};
//vs의 목적은 3d 모델의 각 정점을 2d로 변환하는데 있다. 즉 MVP행렬이라는 변환과정을 뜻한다.
//output의 sv는 GPU가 화면에 그릴 수 있는 클립(Clip)공간을 창출하는데 있다.
//semantic은 인식할 수 있는 태그이자 프로토콜이라 봐야한다. 그리고 이 semantic종류의 texcoord는 이러한 uv데이터를 전달하기 위한 태그로 봐야한다.
//uv는 텍스처 좌표계를 뜻하며, Texture이미지의 어디, 예를 들어 u 0.5 v 0.5는 정중앙의 좌표를 지칭할때 쓰인다.

cbuffer TransformData : register(b0)
{
	float4 offset;
}
//상수버퍼의 유연성에 대해 잘 생각해보자. register에 저장하는 이유는 gpu가 메모리에 가장 빠르게 접근할 수 있기 때문이다.
// IA - VS - RS - PS - OM

VS_OUTPUT VS(VS_INPUT input)
{
	VS_OUTPUT output;
	output.position = input.position + offset;
	output.uv = input.uv;

	return output;
}

Texture2D texture0 : register(t0);
// Texture2D texture1 : register(t1);
SamplerState sampler0 : register(s0);

float4 PS(VS_OUTPUT input) : SV_Target
{
	float4 color = texture0.Sample(sampler0, input.uv);
	
	return color;
}//ps단계에선 앞선 픽셀 묶음을 더 완벽하게 보간. Sampler는 이러한 텍스쳐를 실제로 입혀서, 색상을 확정시키는게 ps단계.

/*
*vs에서는 픽셀을 쳐다보지 않고 클립공간에서의 vertex만 던져준다.
rs에서는 이 vertex를 화면의 pixel에 나타내기 위한 보간작업이다. 
ps에서는 이 pixel의 색상 보정을 끝마치고 텍스쳐를 가져오되, Sampler및 픽셀의 색상을 적용해서 음영처리같은걸 해서 전달해준다. 최종 타겟이 SV_Target이다.
 */