#pragma once
#include "MeshRenderComponent.h"

class PropComponent : public MeshRenderComponent
{
public:
    bool isPickedUp;
    Katamari* katamari;
    PropComponent(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture, float size, DirectX::SimpleMath::Vector3 collOffset, DirectX::SimpleMath::Quaternion rotOffset);
    ~PropComponent() override = default;
	DirectX::BoundingSphere collision;
    DirectX::SimpleMath::Vector3 initRelPos;
    DirectX::SimpleMath::Quaternion inverseKatamariRotation;
    DirectX::SimpleMath::Vector3 originCollisionOffset;
    DirectX::SimpleMath::Quaternion originRotationOffset;
    float gameSize;
    void Update() override;
    void SetPosition(DirectX::SimpleMath::Vector3 p) override;
    void SetRotation(DirectX::SimpleMath::Quaternion q) override;
};
