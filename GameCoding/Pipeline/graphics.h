#pragma once

class Graphics
{
public:
    Graphics(HWND hwnd);
    ~Graphics();

    void RenderBegin();
    void RenderEnd();

    ComPtr<ID3D11Device> GetDevice() {return _device;}
    ComPtr<ID3D11DeviceContext> GetDeviceContext(){return _deviceContext;}
    
private:
    void CreateDeviceAndSwapChain();
    void CreateRenderTargetView();
    void SetViewport();

private:
    HWND _hwnd={};
    // Device & SwapChain
    ComPtr<IDXGISwapChain> _swapChain = nullptr;//전면, 후면 버퍼의 교체 툴 -> prensent로 고속 복사
    ComPtr<ID3D11Device> _device = nullptr;//총괄하는 커맨드센터
    ComPtr<ID3D11DeviceContext> _deviceContext = nullptr;//Device에서 내리는 명령어 집합체
    
    /// RTV
    ComPtr<ID3D11RenderTargetView> _renderTargetView;

    // Misc
    D3D11_VIEWPORT _viewport = {0};
    float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

};
