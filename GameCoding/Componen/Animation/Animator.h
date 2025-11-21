#pragma once


#include "../Component.h"
#include "../../Resource/Animation.h"

class Animator : public Component
{
    using Super = Component;

public:
    Animator();
    virtual ~Animator();

    void Init();
    void Update();

    shared_ptr<Animation> GetCurrentAnimation();
    const Keyframe& GetCurrentKeyframe();

    void SetAnimation(shared_ptr<Animation> animation) { _currentAnimation = animation; }

private:
    float _sumTime = 0.f;

    int32 _currentKeyframeIndex = 0;
    shared_ptr<Animation> _currentAnimation;
};

//Animator는 animation이 가지고 있는 리소스를 재생시키는 모듈이라 봐야한다.
//단일 Animation이 가지고 있는 frameIndex 혹은 현재 Animation이 어떤건지, 업데이트를 해야하는지를 관리한다.