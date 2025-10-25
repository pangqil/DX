#pragma once

#include "Pipeline/graphics.h"

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
	// void CreateDeviceAndSwapChain();
	// void CreateRenderTargetView();
	// void SetViewport();

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

	shared_ptr<Graphics> _graphics;
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

	Vec3 _localPosition ={0.f,0.f,0.f};
	Vec3 _localRotation ={0.f,0.f,0.f};
	Vec3 _localScale ={1.f,1.f,1.f};
};

