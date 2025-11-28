#pragma once
#include "Component.h"

class MonoBehaviour: public Component
{
public:
    using Super = Component;

public:
    MonoBehaviour();
    ~MonoBehaviour();

    virtual void Awake() override;
    virtual void Update() override;
};
//주로 Script라고 불리는 녀석이며, 라이프사이클에 관여하여 해당 오브젝트의 움직임을 정의하게 된다.
//동시에 Script또한 컴포넌트로 쓰인다.