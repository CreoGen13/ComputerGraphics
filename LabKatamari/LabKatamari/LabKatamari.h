#pragma once

#include "Game.h"
#include "OrbitCameraController.h"

class PropComponent;
class KatamariBall;

class LabKatamari : public Game
{
protected:
    KatamariBall* ball;
    OrbitCameraController* orbitCameraController{};
public:
    std::vector<PropComponent*> furniture {};
    LabKatamari();
    void Update() override;
};
