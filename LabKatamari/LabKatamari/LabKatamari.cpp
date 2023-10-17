#include "LabKatamari.h"

#include "PropComponent.h"
#include "QuadComponent.h"
#include "Katamari.h"

using namespace DirectX;
using namespace SimpleMath;

LabKatamari::LabKatamari() : Game(L"Lab Katamari", 800, 800)
{
    srand(static_cast<unsigned>(time(nullptr)));

    katamari = new Katamari(this);
    katamari->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    components_.push_back(katamari);

    QuadComponent* floor = new QuadComponent(this, L"Textures/compost.dds");
    floor->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PI / 2.0f));
    floor->SetScale(Vector3::One * 100.0f);
    components_.push_back(floor);

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* cup = new PropComponent(this, "Models/3.obj", L"Textures/3.dds", 0.4f, Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity);
        cup->SetScale(Vector3(0.4f, 0.4f, 0.4f));
    	cup->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, -0.2f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
    	cup->collision.Radius = 0.8f;
        
        components_.push_back(cup);
        props.push_back(cup);
    }

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* pomegrenade = new PropComponent(this, "Models/6.obj", L"Textures/6.dds", 0.6f, Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity);
        pomegrenade->SetScale(Vector3(0.5f, 0.5f, 0.5f));
        pomegrenade->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.3f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
        pomegrenade->collision.Radius = 0.2f;

    	components_.push_back(pomegrenade);
        props.push_back(pomegrenade);
    }

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* cat = new PropComponent(this, "Models/1.obj", L"Textures/1.dds", 1.2f, Vector3(0.0f, 0.0f, 0.0f), Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PI / 2.0f));
        cat->SetScale(Vector3(0.05f, 0.05f, 0.05f));
        cat->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
        cat->collision.Radius = 0.6f;

    	components_.push_back(cat);
        props.push_back(cat);
    }

    for (int i = 0; i < 5; ++i)
    {
        PropComponent* smile = new PropComponent(this, "Models/5.obj", L"Textures/5.dds", 2.0f, Vector3(0.0f, 0.0f, 0.0f), Quaternion::Identity);
        smile->SetScale(Vector3(0.6f, 0.6f, 0.6f));
        smile->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 1.5f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        smile->collision.Radius = 1.0f;

    	components_.push_back(smile);
        props.push_back(smile);
    }

    cameraController = new KatamariCameraController(this, GetCamera(), katamari);

    inputDevice_->MouseMove.AddRaw(cameraController, &KatamariCameraController::OnMouseMove);
}

void LabKatamari::Update()
{
    cameraController->Update();
    Vector3 dir = Vector3::Zero;
    if (inputDevice_->IsKeyDown(Keys::W))
        dir += cameraController->GetForward();
    if (inputDevice_->IsKeyDown(Keys::S))
        dir -= cameraController->GetForward();
    if (inputDevice_->IsKeyDown(Keys::A))
        dir -= (cameraController->GetForward()).Cross(cameraController->GetUp());
    if (inputDevice_->IsKeyDown(Keys::D))
        dir +=(cameraController->GetForward()).Cross(cameraController->GetUp());
    if (dir.Length() > 0.0f)
        katamari->SetDirection(dir);
    Game::Update();
}
