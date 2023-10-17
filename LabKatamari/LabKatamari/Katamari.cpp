#include "Katamari.h"
#include "Game.h"
#include "LabKatamari.h"
#include "PropComponent.h"

using namespace DirectX;
using namespace SimpleMath;

void Katamari::UpdateSize(float propSize)
{
    float tmp = sqrtf(pow(gameSize, 2) + pow(propSize, 2));
    collision.Radius = tmp;
    position.y = tmp;
    rotationMaxSpeed = 0.1f / (tmp * tmp);
    if (rotationMaxSpeed < 0.005f)
        rotationMaxSpeed = 0.005f;
    moveMaxSpeed = 8.0f * sqrtf(tmp);
    rotationDrag = 0.1f + 0.06f / sqrtf(tmp);
    gameSize = tmp;
}

Katamari::Katamari(Game* game) : SphereComponent(game, 1.0f, 32, 32, L"Textures/ava.dds"),
velocity(Vector3::Zero), collision(position, 1.0f), gameSize(1.0f)
{
    kGame = dynamic_cast<LabKatamari*>(game);
    rotationDrag = 0.14f;
    rotationMaxSpeed = 0.1f;
    moveMaxSpeed = 8.0f;
    moveDrag = 5.0f;
}

void Katamari::Initialize()
{
    SphereComponent::Initialize(); 
}

void Katamari::Draw()
{
    SphereComponent::Draw();
}

void Katamari::Update()
{
    collision.Center = position;
    
    for (auto prop : kGame->props)
    {
        if (collision.Intersects(prop->collision) && !prop->isPickedUp && gameSize > prop->gameSize)
        {
            prop->isPickedUp = true;
            prop->katamari = this;
            prop->initRelPos = prop->GetPosition() - GetPosition();
            rotation.Inverse(prop->inverseKatamariRotation);
            UpdateSize(prop->gameSize);
        }
    }
    
    
    velocity *= 1.0f - moveDrag * game->DeltaTime();

    if(velocity.Length() != 0)
    {
        float t = (velocity.Length() / position.y) * game->DeltaTime();
        Quaternion q = Quaternion::CreateFromAxisAngle(velocity.Cross(Vector3::Up), -t);
        rotation *= q;
    }
    

    SphereComponent::Update();

    position += velocity * game->DeltaTime();
}

void Katamari::Reload()
{
    SphereComponent::Reload();
}

void Katamari::DestroyResources()
{
    SphereComponent::DestroyResources();
}

void Katamari::SetDirection(Vector3 dir)
{
    Vector3 tmp = Vector3(dir.x, 0.0f, dir.z);
    tmp.Normalize();
    velocity = tmp * moveMaxSpeed;
}

void Katamari::SetPosition(Vector3 p)
{
    SphereComponent::SetPosition(p);
}
