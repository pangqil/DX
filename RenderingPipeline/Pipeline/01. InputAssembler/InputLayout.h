#pragma once

class InputLayout
{
public:
	InputLayout(ComPtr<ID3D11Device> device);
	~InputLayout();

	ComPtr<ID3D11InputLayout> GetComPtr() { return _inputLayout; }

	void Create(const vector< D3D11_INPUT_ELEMENT_DESC>& descs, ComPtr<ID3DBlob> blob);
//blob는 쉐이더(hlsl)를 컴파일 한 결과다.
	//blob와 desc를 결합해야 layout이 만들어진다. 이 layout을 통해 vs와 접촉한다.
private:
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11InputLayout> _inputLayout;
};

