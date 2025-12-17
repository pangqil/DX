#include "pch.h"
#include "InstancingManager.h"
#include "GameObject.h"
#include "MeshRenderer.h"
#include "ModelRenderer.h"


void InstancingManager::Render(vector<shared_ptr<GameObject>>& gameObjects)
{
    ClearData();
    RenderMeshRenderer(gameObjects);
}

void InstancingManager::ClearData()
{
    for (auto& pair:_buffers)
    {
        shared_ptr<InstancingBuffer>& buffer=pair.second;
        buffer->ClearData();
    }
}

void InstancingManager::RenderMeshRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
    map<InstanceID, vector<shared_ptr<GameObject>>> cache;
    //InstanceID와 GameObject의 배열(어떻게 보면 고유 ID)
    //즉 ID(재질, Mesh)가 같은 Object끼리 Render하려는 목적의 cache
    for (shared_ptr<GameObject>& gameObject:gameObjects)
    {
        if (gameObject->GetMeshRenderer()==nullptr)//meshrender가 있느냐. 즉 렌더해야될 대상이 아니라면.
            continue;
        //ID는 Mesh와 material 등등 int64,int64로 이루어짐
        const InstanceID instanceId=gameObject->GetMeshRenderer()->GetInstanceID();
        cache[instanceId].push_back(gameObject);//같은 ID끼리 gameobject 
    }
    
    for (auto& pair : cache)
    {//Object친구들
        const vector<shared_ptr<GameObject>>& vec = pair.second;
        
        //if (vec.size() == 1)
        //{
        //	vec[0]->GetMeshRenderer()->RenderSingle();
        //}
        //else
        {
            const InstanceID instanceId = pair.first;

            for (int32 i = 0; i < vec.size(); i++)
            {
                const shared_ptr<GameObject>& gameObject = vec[i];
                InstancingData data;
                data.world = gameObject->GetTransform()->GetWorldMatrix();

                AddData(instanceId, data);
            }//여기서 애들을 다 넣어줌

            //그려줄 애를 하나만 일단 그려야함.
            shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
            vec[0]->GetModelRenderer()->RenderInstancing(buffer);
        }
    }
}


void InstancingManager::RenderModelRenderer(vector<shared_ptr<GameObject>>& gameObjects)
{
    map<InstanceID, vector<shared_ptr<GameObject>>> cache;

    for (shared_ptr<GameObject>& gameObject : gameObjects)
    {
        if (gameObject->GetModelRenderer() == nullptr)
            continue;

        const InstanceID instanceId = gameObject->GetModelRenderer()->GetInstanceID();
        cache[instanceId].push_back(gameObject);
    }

    for (auto& pair : cache)
    {
        const vector<shared_ptr<GameObject>>& vec = pair.second;

        //if (vec.size() == 1)
        //{
        //	vec[0]->GetMeshRenderer()->RenderSingle();
        //}
        //else
        {
            const InstanceID instanceId = pair.first;

            for (int32 i = 0; i < vec.size(); i++)
            {
                const shared_ptr<GameObject>& gameObject = vec[i];
                InstancingData data;
                data.world = gameObject->GetTransform()->GetWorldMatrix();

                AddData(instanceId, data);
            }

            shared_ptr<InstancingBuffer>& buffer = _buffers[instanceId];
            vec[0]->GetModelRenderer()->RenderInstancing(buffer);
        }
    }
}

void InstancingManager::AddData(InstanceID instanceId, InstancingData& data)
{
    if (_buffers.find(instanceID)==_buffers.end())
        _buffers[instanceID]=make_shared<InstancingBuffer>();
    _buffers[instanceID]->AddData(data);
}
