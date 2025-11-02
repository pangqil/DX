#include "pch.h"
#include "GameObject.h"

GameObject::GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> devicecontext)
    :_device(device)
{
    _geometry=make_shared<Geometry<VertexTextureData>>();
    GeometryHelper::CreateRectangle(_geometry);
    
    _vertexBuffer = make_shared<VertexBuffer>(device);
    _vertexBuffer->Create(_geometry->GetVertices());
    
    _indexBuffer = make_shared<IndexBuffer>(device);
    _indexBuffer->Create(_geometry->GetIndices());
    
    _inputLayout = make_shared<InputLayout>(device);
    _inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());

    _vertexShader=make_shared<VertexShader>(device);
    
    _pixelShader=make_shared<PixelShader>(device);
    _pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");
    
    _constantBuffer=make_shared<ConstantBuffer<TransformData>>(device, devicecontext);
    _constantBuffer->Create();
    
    _blendState=make_shared<BlendState>(device);
    _blendState->Create();
    
    _rasterizerState=make_shared<RasterizerState>(device);
    _rasterizerState->Create();
    
    _texture1=make_shared<Texture>(device);
    _texture1->Create(L"Skeleton.png");
    
    _samplerState=make_shared<SamplerState>(device);
    _samplerState->Create();
    
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
}

void GameObject::Render(shared_ptr<Pipeline> pipeline)
{
}
