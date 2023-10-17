#include "PropComponent.h"

#include "Katamari.h"

using namespace DirectX;
using namespace SimpleMath;

PropComponent::PropComponent(Game* g, const std::string fileNameModel, const wchar_t* fileNameTexture, float size, Vector3 collOffset, Quaternion rotOffset) :
    MeshRenderComponent(g, fileNameModel, fileNameTexture), isPickedUp(false), collision(position + collOffset, size), originCollisionOffset(collOffset), originRotationOffset(rotOffset), gameSize(size)
{
    katamari = nullptr;
    rotation = originRotationOffset;
}

void PropComponent::Update()
{
    MeshRenderComponent::Update();

    if(!katamari)
        return;

    if (isPickedUp)
    {
    	SetPosition(katamari->GetPosition() + Vector3::Transform(initRelPos, inverseKatamariRotation * katamari->GetRotation()));
    	SetRotation(inverseKatamariRotation * katamari->GetRotation());
    }
}

void PropComponent::SetPosition(Vector3 p)
{
    collision.Center = p + originCollisionOffset;
    MeshRenderComponent::SetPosition(p);
}
void PropComponent::SetRotation(Quaternion q)
{
    rotation = originRotationOffset * q;
}
