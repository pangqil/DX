#include "pch.h"
#include "InstancingBuffer.h"

InstancingBuffer::InstancingBuffer()
{
	CreateBuffer(MAX_MESH_INSTANCE);
}

InstancingBuffer::~InstancingBuffer()
{
}

void InstancingBuffer::ClearData()
{
	_data.clear();
}

void InstancingBuffer::AddData(InstancingData& data)
{
	_data.push_back(data);
}

void InstancingBuffer::PushData()
{
	const uint32 dataCount = GetCount();
	if (dataCount > _maxCount)
		CreateBuffer(dataCount);

	D3D11_MAPPED_SUBRESOURCE subResource;
	//Map은 Update()함수와 같다고 보면됨.
	DC->Map(_instanceBuffer->GetComPtr().Get(), 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource);
	{//SRV껍데기 열고 닫기(LocK). GPU에 데이터 바꿔치기.
		::memcpy(subResource.pData, _data.data(), sizeof(InstancingData) * dataCount);
	}//CPU데이터 GPU로 복사
	DC->Unmap(_instanceBuffer->GetComPtr().Get(), 0);
}

void InstancingBuffer::CreateBuffer(uint32 maxCount)
{
	_maxCount = maxCount;
	_instanceBuffer = make_shared<VertexBuffer>();//GPU에게 보내기 위한 도구. vertex constant, instance 등등 여러가지...
	
	vector<InstancingData> temp(maxCount);//instance에 쓰일 Data(World Position)생성
	_instanceBuffer->Create(temp, 1, true);//vertices(temp)
}


