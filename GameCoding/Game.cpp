#include "pch.h"
#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;
	
	_graphics=make_shared<Graphics>(hwnd);
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexShader=make_shared<VertexShader>(_graphics->GetDevice());
	_pixelShader=make_shared<PixelShader>(_graphics->GetDevice());
	_constantBuffer=make_shared<ConstantBuffer>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_texture1=make_shared<Texture>(_graphics->GetDevice());
	_pipeline
	
	CreateGeometry();
	CreateVS();
	CreateInputLayout();
	CreatePS();

	CreateRasterizerState();
	CreateSamplerState();
	CreateBlendState();

	_texture1->Create(L"Skeleton.png");
	
	_constantBuffer->Create();
}

void Game::Update()

	// Scale Rotation Translation
	//_transformData.offset.x += 0.003f;
	//_transformData.offset.y += 0.003f;

	Matrix matScale=Matrix::CreateScale(_localScale);
	Matrix matRotation=Matrix::CreateRotationX(_localRotation.x);
	matRotation*=Matrix::CreateRotationY(_localRotation.y);
	matRotation*=Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation=Matrix::CreateTranslation(_localPosition);

	Matrix matWorld=matScale*matRotation* matTranslation;//SRT
	_transformData.matWorld=matWorld;

	_constantBuffer->CopyData(_transformData);
 }

void Game::Render()
{
	_graphics->RenderBegin();

	{
		PipelineInfo info;
		info.inputLayout=_inputLayout;
		info.vertexShader=_vertexShader;
		info.pixelShader=_pixelShader;
		info.rasterizerState=_rasterizerState;
		info.blendState=_blendState;

		_pipeline->UpdatePipeline(info);

		_pipeline->SetVertexBuffer(_vertexBuffer);
		_pipeline->SetIndexBuffer(_indexBuffer);
		_pipeline->SetConstantBuffer(0,SS_VertexShader, _constantBuffer);
		_pipeline->SetTexture(0,SS_PixelShader, _texture1);
		_pipeline->DrawIndexed(_geometry->GetIndexCount(),0,0);
	}

	_graphics->RenderEnd();//호출하게 되면 swapchain써서 후면->전면 고속 복사하고 화면에 그려주기.
}

void Game::CreateGeometry()
{
	GeometryHelper::CreateRectangle(_geometry);
	
	// VertexBuffer
	{//gpu로 보내기 위해 vertices를 버퍼로 변환
		//_vertexBuffer->Create(_vertices);
		_vertexBuffer->Create(_geometry->GetVertices());
	}

	// Index
	{
		_indices = {0, 1, 2, 2, 1, 3};
	}

	// IndexBuffer
	{
		_indexBuffer->Create(_geometry->GetIndices());
	}

}

void Game::CreateInputLayout()//IA단계는 VertexBuffer안에 있는 내용(VS_INPUT)들을 어떻게 해석할 것인가? 
{
	vector<D3D11_INPUT_ELEMENT_DESC> layout
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	_inputLayout->Create(layout, _vertexShader->GetBlob());

	const int32 count = sizeof(layout) / sizeof(D3D11_INPUT_ELEMENT_DESC);
}//vertex shader를 컴파일하면 blob가 결과물로 나온다.

void Game::CreateVS()
{
	LoadShaderFromFile(L"Default.hlsl", "VS", "vs_5_0", _Blob);
 	HRESULT hr = _graphics->GetDevice()->CreateVertexShader(_Blob->GetBufferPointer(), _vsBlob->GetBufferSize(), nullptr, _vertexShader.GetAddressOf());
	CHECK(hr);

	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
}

void Game::CreatePS()
{
	LoadShaderFromFile(L"Default.hlsl", "PS", "ps_5_0", _psBlob);
	HRESULT hr = _graphics->GetDevice()->CreatePixelShader(_psBlob->GetBufferPointer(), _psBlob->GetBufferSize(), nullptr, _pixelShader.GetAddressOf());
	CHECK(hr);

	
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
	
}

void Game::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.FillMode = D3D11_FILL_SOLID;
	desc.CullMode = D3D11_CULL_BACK;
	desc.FrontCounterClockwise = false;

	HRESULT hr = _graphics->GetDevice()->CreateRasterizerState(&desc, _rasterizerState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateSamplerState()
{
	D3D11_SAMPLER_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.AddressU = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressV = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.AddressW = D3D11_TEXTURE_ADDRESS_BORDER;
	desc.BorderColor[0] = 1;
	desc.BorderColor[1] = 0;
	desc.BorderColor[2] = 0;
	desc.BorderColor[3] = 1;
	desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	desc.MaxAnisotropy = 16;
	desc.MaxLOD = FLT_MAX;
	desc.MinLOD = FLT_MIN;
	desc.MipLODBias = 0.0f;

	_graphics->GetDevice()->CreateSamplerState(&desc, _samplerState.GetAddressOf());
}

void Game::CreateBlendState()
{
	D3D11_BLEND_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BLEND_DESC));
	desc.AlphaToCoverageEnable = false;
	desc.IndependentBlendEnable = false;

	desc.RenderTarget[0].BlendEnable = true;
	desc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	desc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	desc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	desc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	desc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	desc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr = _graphics->GetDevice()->CreateBlendState(&desc, _blendState.GetAddressOf());
	CHECK(hr);
}

void Game::CreateSRV()
{
	DirectX::TexMetadata md;
	DirectX::ScratchImage img;
	HRESULT hr = ::LoadFromWICFile(L"Skeleton.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourveView.GetAddressOf());
	CHECK(hr);

	hr = ::LoadFromWICFile(L"Golem.png", WIC_FLAGS_NONE, &md, img);
	CHECK(hr);

	hr = ::CreateShaderResourceView(_graphics->GetDevice().Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourveView2.GetAddressOf());
	CHECK(hr);
}


void Game::LoadShaderFromFile(const wstring& path, const string& name, const string& version, ComPtr<ID3DBlob>& blob)
{
	const uint32 compileFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;

	HRESULT hr = ::D3DCompileFromFile(
		path.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		name.c_str(),
		version.c_str(),
		compileFlag,
		0,
		blob.GetAddressOf(),
		nullptr);

	CHECK(hr);
	
	

}
