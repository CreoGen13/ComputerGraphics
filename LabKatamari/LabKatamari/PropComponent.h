#pragma once
#include "MeshRenderComponent.h"

class PropComponent : public MeshRenderComponent
{
public:
    bool isPickedUp;
    PropComponent(Game* g, std::string fileNameModel, const wchar_t* fileNameTexture, float katSize, DirectX::SimpleMath::Vector3 collOffset);
    ~PropComponent() override = default;
	DirectX::BoundingSphere collision;
    DirectX::SimpleMath::Vector3 initRelPos;
    DirectX::SimpleMath::Quaternion invKbRot;
    DirectX::SimpleMath::Vector3 originCollisionOffset;
    float gameSize;
    void Update() override;
    void SetPosition(DirectX::SimpleMath::Vector3 p) override;
};
