#pragma once

class Monobehaviour: public Component
{
public:
    using Super = Component;

public:
    Monobehaviour();
    ~Monobehaviour();

    virtual void Awake() override;
    virtual void Update() override;
};
