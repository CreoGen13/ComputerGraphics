#pragma once
#include "QuadComponent.h"
#include "SimpleMath.h"

class RacquetComponent :
    public QuadComponent
{
public:
    DirectX::SimpleMath::Rectangle CollisionBox;
    float Speed;
    explicit RacquetComponent(Game* g, SimpleMath::Vector3 color);
    void Update() override;
};