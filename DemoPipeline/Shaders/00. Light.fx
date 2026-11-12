#ifndef _LIGHT_FX_
#define _LIGHT_FX_

#include "00. Global.fx"


//Struct

struct LightDesc
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 emissive;
	float3 direction;
	float padding;
};
/*
	빛을 계산하는데 필요한 속성들을 하나의 구조체로 정의해서 constant buffer로 보내면 
	한번의 호출로 정리되기에 전송 오버헤드를 줄일 수 있음.
*/
struct MaterialDesc
{
	float4 ambient;
	float4 diffuse;
	float4 specular;
	float4 emissive;
};

// ConstBuffer cbuffer

cbuffer LightBuffer
{
	LightDesc GlobalLight;
};

cbuffer MaterialBuffer
{
	MaterialDesc Material;
};
//Light Buffer는 카메라의 위치를 바꾸지 않으면 거의 갱신되지 않는다.
//Material은 Drawcall(물체)단위로 변경된다. 

/////////
// SRV //
/////////

Texture2D DiffuseMap;
Texture2D SpecularMap;
Texture2D NormalMap;

/*
전체적인 분위기인 Ambient는 장면전체의 최소밝기만 상수로 표현하기에 텍스쳐 불필요
외곽선강조는 벡터의 방향성, 즉 직교하는것만 사용하기에 텍스쳐 불필요
각 텍스쳐가 가지고 있는 데이터 필요. 
Normal은 입체감, Specular은 광택(눈뽕), Diffuse는 디테일 사라짐.
*/

//////////////
// Function //
//////////////

float4 ComputeLight(float3 normal, float2 uv, float3 worldPosition)
{
	float4 ambientColor = 0;
	float4 diffuseColor = 0;
	float4 specularColor = 0;
	float4 emissiveColor = 0;

	// Ambient -> light에 대한 ambient * material ambient
	{//전체적인 빛을 어떻게 계산할것인가? 주로 최소 밝기에 대한 영역을 담당한다.
		float4 color = GlobalLight.ambient * Material.ambient;
		ambientColor = DiffuseMap.Sample(LinearSampler, uv) * color;
	}

	// Diffuse -> 표면법선과 빛을 내적한 값 value. 그리고 diffuse(mat, light), color, value 전부곱
	{//빛이 표면에 반사되는 정도이며 또 다르게는 어떤 비율로 빛을 받아들일 것인가.
		float4 color = DiffuseMap.Sample(LinearSampler, uv);
		float value = saturate(dot(normalize(-GlobalLight.direction), normalize(normal)));
		diffuseColor = color * value * GlobalLight.diffuse * Material.diffuse;
	}

	// Specular -> 눈뽕에 대한 조절. 표면에 반사되어 들어온 빛이 눈에 어느정도의 영향을 끼치는가
	{//반사광을 측정 이것을 r이라고 했을떄 R과 camera의 내적하고 0~1로 clamp하고 pow10
		//float3 R = reflect(GlobalLight.direction, normal);
		float3 L = normalize(GlobalLight.direction);
		float3 N = normalize(normal);
		float3 R = L - (2 * N * dot(L, N));
		R = normalize(R);

		float3 cameraPosition = CameraPosition();
		float3 E = normalize(cameraPosition - worldPosition);

		float value = saturate(dot(R, E)); // clamp(0~1)
		float specular = pow(value, 10);

		specularColor = GlobalLight.specular * Material.specular * specular;
	}

	// Emissive -> 외곽선. 카메라와 물체의 벡터를 만들고, 해당 벡터에서 1을 뺌(반전)해서 1에 가까울수록 외곽선 강도조절
	{// emissive라는 1에서 뺀값이 쌔다는것은 코사인 1이라는 직교에 가깝다는 의미.
		float3 cameraPosition = CameraPosition();
		float3 E = normalize(cameraPosition - worldPosition);

		float value = saturate(dot(E, normalize(normal)));
		float emissive = 1.0f - value;

		// min, max, x
		emissive = smoothstep(0.0f, 1.0f, emissive);
		emissive = pow(emissive, 2);

		emissiveColor = GlobalLight.emissive * Material.emissive * emissive;
	}

	return ambientColor + diffuseColor + specularColor + emissiveColor;
}

void ComputeNormalMapping(inout float3 normal, float3 tangent, float2 uv)
{
	// [0,255] 범위에서 [0,1]로 변환
	float4 map = NormalMap.Sample(LinearSampler, uv);
	if (any(map.rgb) == false)
		return;

	float3 N = normalize(normal); // z
	float3 T = normalize(tangent); // x
	float3 B = normalize(cross(N, T)); // y
	float3x3 TBN = float3x3(T, B, N); // TS -> WS

	// [0,1] 범위에서 [-1,1] 범위로 변환
	float3 tangentSpaceNormal = (map.rgb * 2.0f - 1.0f);
	float3 worldNormal = mul(tangentSpaceNormal, TBN);

	normal = worldNormal;
}

#endif

