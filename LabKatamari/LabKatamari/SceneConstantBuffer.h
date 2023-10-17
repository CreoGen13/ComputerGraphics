#pragma once
#include "SimpleMath.h"

struct SceneConstantBuffer
{
    DirectX::SimpleMath::Vector4 LightPos;
    DirectX::SimpleMath::Vector4 LightColor;
    DirectX::SimpleMath::Vector4 AmbientSpecularPowType;
};
