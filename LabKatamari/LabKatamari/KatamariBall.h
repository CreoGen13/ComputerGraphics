#pragma once

#include "SphereComponent.h"

class KatamariBallOutline;
class LabKatamari;

class KatamariBall :  public SphereComponent
{
protected:
    LabKatamari* kGame;
    void UpdateSize(float absorbedSize);
public:
    float rotationDrag;
    float rotationMaxSpeed;
    float moveMaxSpeed;
    float moveDrag;
    DirectX::SimpleMath::Vector3 velocity;
    DirectX::BoundingSphere collision;
    float gameSize;
    KatamariBall(Game* game);
    void Initialize() override;
    void Draw() override;
    void Update() override;
    void Reload() override;
    void DestroyResources() override;
    void SetDirection(DirectX::SimpleMath::Vector3 dir);
    void SetPosition(DirectX::SimpleMath::Vector3 p) override;
};
