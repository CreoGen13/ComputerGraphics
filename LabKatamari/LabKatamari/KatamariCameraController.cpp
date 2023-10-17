#include "KatamariCameraController.h"
#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;

KatamariCameraController::KatamariCameraController(Game* g, Camera* c, BaseGameComponent* t) : game(g), camera(c), target(t),
    rotation(Quaternion::Identity), radius(10.0f), sensitivityX(0.004f), sensitivityY(0.004f), isLMBActivated(true)
{
}

void KatamariCameraController::OnMouseMove(const InputDevice::MouseMoveEventArgs& args)
{
    if (game->GetInputDevice()->IsKeyDown(Keys::LeftButton) || !isLMBActivated)
    {
        const Vector3 tmp = Vector3::Transform(Vector3::Right, rotation);
        rotation *= Quaternion::CreateFromAxisAngle(tmp, sensitivityY * -game->GetInputDevice()->MouseOffset.y);
        rotation *= Quaternion::CreateFromAxisAngle(Vector3::Up, - sensitivityX * game->GetInputDevice()->MouseOffset.x);
    }
    if ((radius > 5.0 || game->GetInputDevice()->MouseWheelDelta < 0) && (radius < 30.0 || game->GetInputDevice()->MouseWheelDelta > 0))
        radius -= 0.01f * static_cast<float>(game->GetInputDevice()->MouseWheelDelta);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void KatamariCameraController::Update()
{
    camera->Position = target->GetPosition() - GetForward() * radius;
    camera->Up = Vector3::Transform(Vector3::Up, rotation);
    camera->Target = target->GetPosition();
}

Vector3 KatamariCameraController::GetForward() const
{
    return Vector3::Transform(Vector3::Forward, rotation);
}

Vector3 KatamariCameraController::GetUp() const
{
    return Vector3::Transform(Vector3::Up, rotation);
}
