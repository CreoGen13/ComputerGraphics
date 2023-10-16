#include "KatamariBall.h"
#include "Game.h"
#include "LabKatamari.h"
#include "PropComponent.h"

using namespace DirectX;
using namespace SimpleMath;

void KatamariBall::UpdateSize(float absorbedSize)
{
    float tmp = sqrtf(gameSize * gameSize + absorbedSize * absorbedSize);
    collision.Radius = tmp;
    position.y = tmp;
    rotationMaxSpeed = 0.1f / (tmp * tmp);
    if (rotationMaxSpeed < 0.005f)
        rotationMaxSpeed = 0.005f;
    moveMaxSpeed = 8.0f * sqrtf(tmp);
    rotationDrag = 0.1f + 0.06f / sqrtf(tmp);
    gameSize = tmp;
}

KatamariBall::KatamariBall(Game* game) : SphereComponent(game, 1.0f, 32, 32, L"Textures/ava.dds"),
velocity(Vector3::Zero), collision(position, 1.0f), gameSize(1.0f)
{
    kGame = dynamic_cast<LabKatamari*>(game);
    rotationDrag = 0.14f;
    rotationMaxSpeed = 0.1f;
    moveMaxSpeed = 8.0f;
    moveDrag = 5.0f;
}

void KatamariBall::Initialize()
{
    SphereComponent::Initialize(); 
}

void KatamariBall::Draw()
{
    SphereComponent::Draw();
}

void KatamariBall::Update()
{
    collision.Center = position;
    
    for (auto furn : kGame->furniture)
    {
        if (collision.Intersects(furn->collision) && !furn->isPickedUp && gameSize > furn->gameSize)
        {
            furn->isPickedUp = true;
            furn->kb = this;
            furn->initRelPos = furn->GetPosition() - GetPosition();
            rotation.Inverse(furn->invKbRot);
            UpdateSize(furn->gameSize);
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

void KatamariBall::Reload()
{
    SphereComponent::Reload();
}

void KatamariBall::DestroyResources()
{
    SphereComponent::DestroyResources();
}

void KatamariBall::SetDirection(Vector3 dir)
{
    Vector3 tmp = Vector3(dir.x, 0.0f, dir.z);
    tmp.Normalize();
    velocity = tmp * moveMaxSpeed;
}

void KatamariBall::SetPosition(Vector3 p)
{
    SphereComponent::SetPosition(p);
}
