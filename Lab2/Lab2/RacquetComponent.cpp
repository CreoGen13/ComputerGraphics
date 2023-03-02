#include "RacquetComponent.h"
#include "Game.h"

using namespace DirectX;

RacquetComponent::RacquetComponent(Game* g, SimpleMath::Vector3 color) : QuadComponent(g, color)
{
	DirectX::SimpleMath::Vector4 pointsTmp[8] = {
		SimpleMath::Vector4(0.02f, 0.15f, 0.5f, 1.0f),	SimpleMath::Vector4(color.x, color.y, color.z, 1.0f),
		SimpleMath::Vector4(-0.02f, -0.15f, 0.5f, 1.0f),	SimpleMath::Vector4(color.x, color.y, color.z, 1.0f),
		SimpleMath::Vector4(0.02f, -0.15f, 0.5f, 1.0f),	SimpleMath::Vector4(color.x, color.y, color.z, 1.0f),
		SimpleMath::Vector4(-0.02f, 0.15f, 0.5f, 1.0f),	SimpleMath::Vector4(color.x, color.y, color.z, 1.0f),
	};
	std::swap(points, pointsTmp);
	Speed = 1.7f;
	CollisionBox = SimpleMath::Rectangle(-0.02f * 800, -0.15f * 800, 0.04f * 800, 0.3f * 800);
}

void RacquetComponent::Update()
{
	CollisionBox.x = -0.01f * 800 + offset.x * 800;
	CollisionBox.y = -0.1f * 800 + offset.y * 800;
	QuadComponent::Update();
}
