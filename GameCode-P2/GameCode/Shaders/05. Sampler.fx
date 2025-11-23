matrix World;
matrix View;
matrix Projection;
Texture2D Texture0;
uint Address;

struct VertexInput
{
	float4 position : POSITION;
    float2 uv : TEXCOORD;
};

struct VertexOutput
{
	float4 position : SV_POSITION;
    float2 uv : TEXCOORD;
};

VertexOutput VS(VertexInput input)
{
	VertexOutput output;
    output.position = mul(input.position, World);
    output.position = mul(output.position, View);
    output.position = mul(output.position, Projection);
	
    output.uv = input.uv;
	
	return output;
}

SamplerState Sampler0;



//Filter -> 확대/축소의 중간값(100% 비율 측정)
//Address -> UV가 1보다 크다면, 나머지부분을 어떻게 처리할것인가

SamplerState SamplerAddressWrap
{
    AddressU = Wrap;
    AddressV = Wrap;
};
SamplerState SamplerAddressMirror
{
    AddressU = Mirror;
    AddressV = Mirror;
};
SamplerState SamplerAddressClamp
{
    AddressU = Clamp;
    AddressV = Clamp;
};
SamplerState SamplerAddressBorder
{
    AddressU = Border;
    AddressV = Border;
    BorderColor = float(1, 0, 0, 1);
};

float4 PS(VertexOutput input) : SV_TARGET
{
    if(Address=0)
        return Texture0.Sample(SamplerAddressWrap, input.up);
    
    if (Address = 1)
        return Texture0.Sample(SamplerAddressMirror, input.up);
    
    if (Address = 2)
        return Texture0.Sample(SamplerAddressClamp, input.up);
    
    if (Address = 3)
        return Texture0.Sample(SamplerAddresBorder, input.up);
    
    return Texture0.Sample(Sampler0, input.uv);
}

technique11 T0
{
	pass P0
	{
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}

	pass P1
	{
        SetRasterizerState(FillModeWireFrame);
		SetVertexShader(CompileShader(vs_5_0, VS()));
		SetPixelShader(CompileShader(ps_5_0, PS()));
	}
};

