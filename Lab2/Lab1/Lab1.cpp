#include "Lab1.h"
#include "TriangleComponent.h"

Lab1::Lab1(LPCWSTR name, int screenWidth, int screenHeight) : Game(name, screenWidth, screenHeight)
{
	Components.push_back(new TriangleComponent(this, 0.5f, 0.5f));
	Components.push_back(new TriangleComponent(this, -0.5f, -0.5f));
}
Lab1::~Lab1()
{

}

void Lab1::Draw()
{
	float color[]{ TotalTime, 0.1f, 0.1f, 1.0f };
	Context->ClearRenderTargetView(RenderView, color);

	for (auto component : Components)
	{
		component->Draw();
	}
}
