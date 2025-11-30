#include "pch.h"
#include "RenderManager.h"
#include "Camera.h"

void RenderManager::Init(shared_ptr<Shader> shader)
{
	_shader = shader;

	_globalBuffer = make_shared<ConstantBuffer<GlobalDesc>>();
	_globalBuffer->Create();
	_globalEffectBuffer = _shader->GetConstantBuffer("GlobalBuffer");

	_transformBuffer = make_shared<ConstantBuffer<TransformDesc>>();
	_transformBuffer->Create();
	_transformEffectBuffer = _shader->GetConstantBuffer("TransformBuffer");

	_lightBuffer = make_shared<ConstantBuffer<LightDesc>>();
	_lightBuffer->Create();
	_lightEffectBuffer = _shader->GetConstantBuffer("LightBuffer");

	_materialBuffer = make_shared<ConstantBuffer<MaterialDesc>>();
	_materialBuffer->Create();
	_materialEffectBuffer = _shader->GetConstantBuffer("MaterialBuffer");
}

void RenderManager::Update()
{
	PushGlobalData(Camera::S_MatView, Camera::S_MatProjection);
}

void RenderManager::PushGlobalData(const Matrix& view, const Matrix& projection)
{
	_globalDesc.V = view;
	_globalDesc.P = projection;
	_globalDesc.VP = view * projection;
	_globalDesc.VInv = view.Invert();
	_globalBuffer->CopyData(_globalDesc);
	_globalEffectBuffer->SetConstantBuffer(_globalBuffer->GetComPtr().Get());
}

void RenderManager::PushTransformData(const TransformDesc& desc)
{
	_transformDesc = desc;
	_transformBuffer->CopyData(_transformDesc);
	_transformEffectBuffer->SetConstantBuffer(_transformBuffer->GetComPtr().Get());
}

void RenderManager::PushLightData(const LightDesc& desc)
{
	_lightDesc = desc;
	_lightBuffer->CopyData(_lightDesc);
	_lightEffectBuffer->SetConstantBuffer(_lightBuffer->GetComPtr().Get());
}

void RenderManager::PushMaterialData(const MaterialDesc& desc)
{
	_materialDesc = desc;
	_materialBuffer->CopyData(_materialDesc);
	_materialEffectBuffer->SetConstantBuffer(_materialBuffer->GetComPtr().Get());
}
//desc는 데이터의 규격, buffer에 desc를 담아 gpu에 전송하는게 목적이다.
//버퍼를 최신화 하기 위해 copydata를 통해 desc구조체를 담고, 이걸 effect를 이용해 push를 한다.
//바인딩(셰이더(GPU)에 연결하는 과정)을 자동으로 처리하는게 EffectBuffer의 역할이다.