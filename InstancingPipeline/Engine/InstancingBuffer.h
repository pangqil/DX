#pragma once

class VertexBuffer;

struct InstancingData {
	Matrix world;
};

#define MAX_MESH_INSTANCE 500

class InstancingBuffer
{
public:
	InstancingBuffer();
	~InstancingBuffer();
public:
	void ClearData();
	void AddData(InstancingData& data);
	void PushData();
	//Mesh데이터(정점, UV)는 모든 인스턴스가 공유한다. Transform은 그렇지 않다.
public:
	uint32 GetCount() { return static_cast<uint32>(_data.size()); }
	shared_ptr<VertexBuffer> GetBuffer() { return _instanceBuffer; }

private:
	void CreateBuffer(uint32 maxCount = MAX_MESH_INSTANCE);


private:
	uint64						_instancedId = 0;
	shared_ptr<VertexBuffer>	_instanceBuffer;
	uint32						_maxCount = 0;
	vector<InstancingData>		_data;

};


