#pragma once

#include "Game.h"
#include "KatamariCameraController.h"

class PropComponent;
class Katamari;

class LabKatamari : public Game
{
protected:
    Katamari* katamari;
    KatamariCameraController* cameraController{};
public:
    std::vector<PropComponent*> props {};
    LabKatamari();
    void Update() override;
};
