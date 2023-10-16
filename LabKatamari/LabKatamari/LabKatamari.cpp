#include "LabKatamari.h"

#include "PropComponent.h"
#include "QuadComponent.h"
#include "KatamariBall.h"

using namespace DirectX;
using namespace SimpleMath;

LabKatamari::LabKatamari() : Game(L"Lab Katamari", 800, 800)
{
    srand(static_cast<unsigned>(time(nullptr)));

    ball = new KatamariBall(this);
    ball->SetPosition(Vector3(0.0f, 1.0f, 0.0f));
    components_.push_back(ball);

    QuadComponent* quad = new QuadComponent(this, L"Textures/compost.dds");
    quad->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PI / 2.0f));
    quad->SetScale(Vector3::One * 100.0f);
    components_.push_back(quad);

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* cup = new PropComponent(this, "Models/3.obj", L"Textures/3.dds", 0.4f, Vector3(0.0f, 0.0f, 0.0f));
        cup->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, -0.2f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
        cup->collision.Radius = 0.8f;
        cup->SetScale(Vector3(0.4f, 0.4f, 0.4f));
        components_.push_back(cup);
        furniture.push_back(cup);
    }

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* pomegrenade = new PropComponent(this, "Models/6.obj", L"Textures/6.dds", 0.6f, Vector3(0.0f, 0.0f, 0.0f));
        pomegrenade->SetScale(Vector3(0.5f, 0.5f, 0.5f));
        pomegrenade->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.3f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
        pomegrenade->collision.Radius = 0.1f;
        components_.push_back(pomegrenade);
        furniture.push_back(pomegrenade);
    }

    for (int i = 0; i < 10; ++i)
    {
        PropComponent* cat = new PropComponent(this, "Models/1.obj", L"Textures/1.dds", 1.2f, Vector3(0.0f, 0.0f, 0.0f));
        cat->SetScale(Vector3(0.05f, 0.05f, 0.05f));
        cat->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 0.0f, static_cast<float>(rand()) / RAND_MAX  * 100.0f - 50.0f));
        cat->SetRotation(Quaternion::CreateFromAxisAngle(Vector3::Right, XM_PI / 2.0f));
        cat->collision.Radius = 0.2f;
        components_.push_back(cat);
        furniture.push_back(cat);
    }

    for (int i = 0; i < 5; ++i)
    {
        PropComponent* smile = new PropComponent(this, "Models/5.obj", L"Textures/5.dds", 2.0f, Vector3(0.0f, 0.0f, 0.0f));
        smile->SetScale(Vector3(0.6f, 0.6f, 0.6f));
        smile->SetPosition(Vector3(static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f, 1.5f, static_cast<float>(rand()) / RAND_MAX * 100.0f - 50.0f));
        smile->collision.Radius = 0.2f;
        components_.push_back(smile);
        furniture.push_back(smile);
    }

    orbitCameraController = new OrbitCameraController(this, GetCamera(), ball);
    orbitCameraController->isLMBActivated = true;

    inputDevice_->MouseMove.AddRaw(orbitCameraController, &OrbitCameraController::OnMouseMove);
}

void LabKatamari::Update()
{
    orbitCameraController->Update();
    Vector3 dir = Vector3::Zero;
    if (inputDevice_->IsKeyDown(Keys::W))
        dir += orbitCameraController->GetForward();
    if (inputDevice_->IsKeyDown(Keys::S))
        dir -= orbitCameraController->GetForward();
    if (inputDevice_->IsKeyDown(Keys::A))
        dir -= (orbitCameraController->GetForward()).Cross(orbitCameraController->GetUp());
    if (inputDevice_->IsKeyDown(Keys::D))
        dir +=(orbitCameraController->GetForward()).Cross(orbitCameraController->GetUp());
    if (dir.Length() > 0.0f)
        ball->SetDirection(dir);
    Game::Update();
}
