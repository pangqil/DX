#pragma once

class GameObject
{
public:
    GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> devicecontext);
    ~GameObject();

    void Update();
    void Render(shared_ptr<Pipeline> pipeline);
private:
    ComPtr<ID3D11Device> _device;

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
private:
    TransformData _transformdata;
    shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

};
