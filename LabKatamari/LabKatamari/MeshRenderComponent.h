#pragma once

#include <string>
#include "BaseRenderComponent.h"
#include <assimp/scene.h>

class Katamari;

class MeshRenderComponent : public BaseRenderComponent
{
protected:
    const std::string fNameModel;
    void ProcessNode(aiNode* node, const aiScene* scene);
    void ProcessMesh(aiMesh* mesh, const aiScene* scene);
public:
    MeshRenderComponent(Game* g, const std::string& fileNameModel, const wchar_t* fileNameTexture);
    ~MeshRenderComponent() override = default;
    void Initialize() override;
    void SetPosition(DirectX::SimpleMath::Vector3 p) override { position = p; }
    void SetRotation(DirectX::SimpleMath::Quaternion q) override { rotation = q; }
    void SetScale(DirectX::SimpleMath::Vector3 s) override { scale = s; }
};
