#pragma once
#include "GameComponent.h"
#include <d3d.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include "SimpleMath.h"

using namespace DirectX;
#define TriangleCount 20

class CircleComponent : public GameComponent
{
protected:
	ID3D11InputLayout* layout;
	ID3D11PixelShader* pixelShader;
	ID3DBlob* pixelShaderByteCode;
	SimpleMath::Vector4 points[TriangleCount * 6];
	ID3D11RasterizerState* rastState;
	ID3D11VertexShader* vertexShader;
	ID3DBlob* vertexShaderByteCode;
	int indices[TriangleCount * 3];
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11Buffer* constBuffer;
	UINT strides[1];
	UINT offsets[1];
	SimpleMath::Vector4 offset;
public:
	CircleComponent(Game* g, SimpleMath::Vector3 color);
	virtual ~CircleComponent();
	void DestroyResources() override;
	void Draw() override;
	void Initialize() override;
	void Update() override;
	void Reload() override;
	void SetPosition(float x, float y);
	void SetPosition(DirectX::SimpleMath::Vector2 pos);
	void SetY(float y);
	void SetX(float x);
	float GetX() const;
	float GetY() const;
	SimpleMath::Vector2 GetPosition() const;
};

