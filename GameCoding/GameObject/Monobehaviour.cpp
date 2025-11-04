#include "pch.h"
#include "Monobehaviour.h"

Monobehaviour::Monobehaviour():Super(ComponentType::Script)
{
}

Monobehaviour::~Monobehaviour()
{
}

void Monobehaviour::Awake()
{
    Component::Awake();
}

void Monobehaviour::Update()
{
    Component::Update();
}
