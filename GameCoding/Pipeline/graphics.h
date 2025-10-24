#pragma one
#include <memory>

class Graphics{
public:
    Graphics(HWND hwnd);
    ~Graphics();

    void RenderBegin();
    void RenderEnd();

    void CreateDeviceAndSwapChain();
    void CreateRenderTargetView();
    void SetViewport();


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
    HWND _hwnd;
    uint32 _width = 0;
    uint32 _height = 0;

    shared_ptr<Graphics> _graphics;
private:


};
