#pragma once

#include "BaseGameComponent.h"
#include "InputDevice.h"
#include "SimpleMath.h"

class BaseGameComponent;
class Game;
class Camera;

class KatamariCameraController
{
protected:
    Game* game;
    Camera* camera;
    BaseGameComponent* target;
    DirectX::SimpleMath::Quaternion rotation;
    float radius;
    float sensitivityX;
    float sensitivityY;
public:
    bool isLMBActivated;
    KatamariCameraController(Game* g, Camera* c, BaseGameComponent* t);
    void OnMouseMove(const InputDevice::MouseMoveEventArgs& args);
    void Update();
    DirectX::SimpleMath::Vector3 GetForward() const;
    DirectX::SimpleMath::Vector3 GetUp() const;
    void SetSensitivity(float sX, float sY) { sensitivityX = sX; sensitivityY = sY; }
    void SetSensitivityX(float sX) { sensitivityX = sX; }
    void SetSensitivityY(float sY) { sensitivityY = sY; }
    float GetSensitivityX() const { return sensitivityX; }
    float GetSensitivityY() const { return sensitivityX; }
};
