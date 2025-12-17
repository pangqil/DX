#pragma once

class VertexBuffer
{
public:
	VertexBuffer();
	~VertexBuffer();

	ComPtr<ID3D11Buffer> GetComPtr() { return _vertexBuffer; }
	uint32 GetStride() { return _stride; }
	uint32 GetOffset() { return _offset; }
	uint32 GetCount() { return _count; }

	template<typename T>
	void Create(const vector<T>& vertices, uint32 slot = 0, bool cpuWrite = false, bool gpuWrite = false)
	{
		_stride = sizeof(T);//Data크기만큼
		_count = static_cast<uint32>(vertices.size());

		_slot = slot;
		_cpuWrite = cpuWrite;
		_gpuWrite = gpuWrite;

		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.ByteWidth = (uint32)(_stride * _count);

		if (cpuWrite == false && gpuWrite == false)
		{
			desc.Usage = D3D11_USAGE_IMMUTABLE; // CPU Read, GPU Read
		}
		else if (cpuWrite == true && gpuWrite == false)
		{
			desc.Usage = D3D11_USAGE_DYNAMIC; // CPU Write, GPU Read
			desc.CPUAccessFlags = D3D10_CPU_ACCESS_WRITE;
		}
		else if (cpuWrite == false && gpuWrite == true) // CPU Read, GPU Write
		{
			desc.Usage = D3D11_USAGE_DEFAULT;
		}
		else
		{
			desc.Usage = D3D11_USAGE_STAGING;
			desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		}
		//GPU가 최종적으로 볼 데이터가 이 SubResource
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(data));
		data.pSysMem = vertices.data();//vertices.data()는 시작주소를 반환해버림.
		//최종적으로 GPU에 데이터를 생성하기 위해 CreateBuffer()를 함. data는 vertex의 시작주소. 이를 desc에 전달된 크기만큼 저장.
		//->GPU에 공간을 할당하고 복사해라. VertexBuffer에 GPU버퍼(다음 쓸곳) 주소를 저장하라
		HRESULT hr = DEVICE->CreateBuffer(&desc, &data, _vertexBuffer.GetAddressOf());
		CHECK(hr);
		
	}
	void PushData()
	{
		DC->IASetVertexBuffers(_slot, 1, _vertexBuffer.GetAddressOf(), &_stride, &_offset);
	}

private:
	ComPtr<ID3D11Buffer> _vertexBuffer;

	uint32 _stride = 0;
	uint32 _offset = 0;
	uint32 _count = 0;

	uint32 _slot=0;
	bool _cpuWrite = false;
	bool _gpuWrite=false;
};
