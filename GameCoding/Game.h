#pragma once
#include <string>


class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:
	void RenderBegin();
	void RenderEnd();

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	void CreateGeometry();
	void CreateInputLayout();
	void CreateVS();
	void CreatePS();

	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();

	void CreateConstantBuffer();

	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// Device & SwapChain
	ComPtr<ID3D11Device> _device = nullptr;//총괄하는 커맨드센터
	ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;//Device에서 내리는 명령어 집합체
	ComPtr<IDXGISwapChain> _swapChain = nullptr;//전면, 후면 버퍼의 교체 툴 -> prensent로 고속 복사

	/// RTV
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc
	D3D11_VIEWPORT _viewport = {0};
	float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

private:
	// Geometry
	vector<Vertex> _vertices;//처음엔 CPU에 있음
	ComPtr<ID3D11Buffer> _vertexBuffer = nullptr;//GPU로 가기 위해 버퍼로 변환 필요
	vector<uint32> _indices;
	ComPtr<ID3D11Buffer> _indexBuffer = nullptr;
	ComPtr<ID3D11InputLayout> _inputLayout = nullptr;//쉐이더(GPU)로 보낼 VertexBuffer에 대한 구조체 설정

	// VS
	ComPtr<ID3D11VertexShader> _vertexShader = nullptr;
	ComPtr<ID3DBlob> _vsBlob = nullptr;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// PS
	ComPtr<ID3D11PixelShader> _pixelShader = nullptr;
	ComPtr<ID3DBlob> _psBlob = nullptr;

	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView2 = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;
	// [ CPU<->RAM ] [GPU<->VRAM]
private:
	// SRT
	TransformData _transformData;
	ComPtr<ID3D11Buffer> _constantBuffer;//여러 물체의 Position, Rotation을 설정하는 변수
};

