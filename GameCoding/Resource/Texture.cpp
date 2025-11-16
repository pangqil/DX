#include "pch.h"
#include "Texture.h"

Texture::Texture(ComPtr<ID3D11Device> device): _device(device)
{
}

Texture::~Texture()
{
}

void Texture::Create(const wstring& path)
{
    DirectX::TexMetadata md;
    DirectX::ScratchImage img;
    HRESULT hr = ::LoadFromWICFile(L"Skeleton.png", WIC_FLAGS_NONE, &md, img);
    CHECK(hr);

    hr = ::CreateShaderResourceView(_device.Get(), img.GetImages(), img.GetImageCount(), md, _shaderResourveView.GetAddressOf());
    CHECK(hr);

}
