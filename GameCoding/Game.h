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

	shared_ptr<VertexShader> _vertexShader = nullptr;
	shared_ptr<PixelShader> _pixelShader = nullptr;

	shared_ptr<Texture> _texture1;
	shared_ptr<Texture> _texture2;

	shared_ptr<RasterizerState> _rasterizerState;
	shared_ptr<SamplerState> _samplerState;
	shared_ptr<BlendState> _blendState;

	shared_ptr<Pipeline> _pipeline;
	
	// SRV
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView = nullptr;
	ComPtr<ID3D11ShaderResourceView> _shaderResourveView2 = nullptr;

private:
	// SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition ={0.f,0.f,0.f};
	Vec3 _localRotation ={0.f,0.f,0.f};
	Vec3 _localScale ={1.f,1.f,1.f};
};

