#pragma once

template<typename T>
class ConstantBuffer
{
public:
	ConstantBuffer() { }
	~ConstantBuffer() { }

	ComPtr<ID3D11Buffer> GetComPtr() { return _constantBuffer; }
	
	void Create()
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Usage = D3D11_USAGE_DYNAMIC; // CPU_Write + GPU_Read
		desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;//상수버퍼로 사용함
		desc.ByteWidth = sizeof(T);//사이즈는 T형태만큼 할당
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;//CPU 쓰는 용도로 할게

		HRESULT hr = DEVICE->CreateBuffer(&desc, nullptr, _constantBuffer.GetAddressOf());
		CHECK(hr);
	}
	// 버퍼는 desc, Memory, Usage, Flags, ByteWidth, Access를 인자로 가진다.
	// hr은 디바이스에 버퍼를 만들었는지에 대한 성공 여부를 판별하는 플래그다.
	void CopyData(const T& data)
	{
		D3D11_MAPPED_SUBRESOURCE subResource;
		ZeroMemory(&subResource, sizeof(subResource));

		DC->Map(_constantBuffer.Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		::memcpy(subResource.pData, &data, sizeof(data));
		DC->Unmap(_constantBuffer.Get(), 0);
	}
	// 이미 할당된 GPU 공간에 데이터를 복사하여 갱신하는 형태이다.(Drawcall)이라고 불린다.
	//memcpy를 통해 데이터를 옮긴다. 이때 subresource를 data에 담는다.
	//this자체가 buffer이기에 교체할 data를 인자로 받는 형태이다.
private:
	ComPtr<ID3D11Buffer> _constantBuffer;
};
