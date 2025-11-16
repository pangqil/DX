#pragma once
#include "Manager/Resource/ResourceBase.h"

class Texture : public ResourceBase
{
    using Super=ResourceBase;
public:
    Texture(ComPtr<ID3D11Device> device);
    ~Texture();

    ComPtr<ID3D11ShaderResourceView> GetComPtr(){return _shaderResourveView;}
    void Create(const wstring& path);
    
    ComPtr<ID3D11Device> _device;
    ComPtr<ID3D11ShaderResourceView> _shaderResourveView = nullptr;
};
