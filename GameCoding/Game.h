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

	//RenderBegin();
	//RenderEnd();
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


	void LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob);

private:
	HWND _hwnd;
	//width, height=0; -> init의 GWinsizeX, Bufferdesc.height, setviewport
	shared_ptr<Graphics> _graphics;

private:
	//Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;//쉐이더(GPU)로 보낼 VertexBuffer에 대한 구조체 설정

	ComPtr<VertexShader> _vertexShader = nullptr;
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;
	ComPtr<PixelShader> _pixelShader = nullptr;

	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;
	
	
	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView2 = nullptr;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;
	// [ CPU<->RAM ] [GPU<->VRAM]
private:
	// SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition ={0.f,0.f,0.f};
	Vec3 _localRotation ={0.f,0.f,0.f};
	Vec3 _localScale ={1.f,1.f,1.f};
};

