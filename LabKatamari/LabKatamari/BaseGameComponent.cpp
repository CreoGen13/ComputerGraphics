#include "BaseGameComponent.h"
#include "Game.h"

using namespace DirectX;
using namespace SimpleMath;

BaseGameComponent::BaseGameComponent(Game* g) : game(g), position(Vector3::Zero), rotation(Quaternion::Identity), scale(Vector3::One)
{
}
