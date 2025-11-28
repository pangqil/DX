#pragma once

#include "../Component.h"

class Transform;
class MonoBehaviour;
class Camera;
class MeshRenderer;
class Animator;

class GameObject:public enable_shared_from_this<GameObject>
{
public:
    GameObject(ComPtr<ID3D11Device> device, ComPtr<ID3D11DeviceContext> devicecontext);
    ~GameObject();

    void Awake();
    void Start();
    void Update();
    void LateUpdate();
    void FixedUpdate();

    shared_ptr<Component> GetFixedComponent(ComponentType type);
    shared_ptr<Transform> GetTransform();
    shared_ptr<Camera> GetCamera();
    shared_ptr<MeshRenderer> GetMeshRenderer();
    shared_ptr<Animator> GetAnimator();
    
    shared_ptr<Transform> GetOrAddTransform();
    void AddComponent(shared_ptr<Component> component);

private:
    ComPtr<ID3D11Device> _device;

protected:
    array<shared_ptr<Component>, FIXED_COMPONENT_COUNT> _components;
    vector<shared_ptr<MonoBehaviour>> _scripts;
};
/*
 해당 Object는 Unity의 엔진 구조를 모방하였다.
 기본 속성 - Transform, ComponentType, Camera, MeshRenderer, Animator가 요소다.
 보조 속성 - Component, Script이며 여기에 Object의 각 기본 속성들이 포함된다.
 */