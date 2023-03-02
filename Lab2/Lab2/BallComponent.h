#pragma once
#include "CircleComponent.h"
#include "BallComponent.h"

class Lab2;

class BallComponent :
    public CircleComponent
{
private:
    Lab2* lab2;
    void GenRndDirection();
public:
    float Speed;
    DirectX::SimpleMath::Vector2 Direction;
    BallComponent(Game* g);
    void Update() override;
};

