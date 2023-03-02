#include "Lab2.h"
#include "Keys.h"
#include <string>

static float DifficultyCurve(unsigned ballHits)
{
    return 5.0f / (1.0f + exp(-static_cast<float>(ballHits) / 8.0f + 4.0f)) + 1.0f;
}

void Lab2::Update()
{
    ball->Speed = DifficultyCurve(ballHits);
    if (InputDev->IsKeyDown(Keys::Escape))
        isExitRequested = true;
    if (state == PONG_STATE_COOLDOWN && std::chrono::steady_clock::now() >= ContinueTime)
        state = PONG_STATE_NORMAL;

    if (InputDev->IsKeyDown(Keys::W) && racquetBlue->GetY() < 0.8f)
        racquetBlue->SetY(racquetBlue->GetY() + DeltaTime * racquetBlue->Speed);
    if (InputDev->IsKeyDown(Keys::S) && racquetBlue->GetY() > -0.8f)
        racquetBlue->SetY(racquetBlue->GetY() - DeltaTime * racquetBlue->Speed);


    if (InputDev->IsKeyDown(Keys::Up) && racquetRed->GetY() < 0.8f)
        racquetRed->SetY(racquetRed->GetY() + DeltaTime * racquetRed->Speed);
    if (InputDev->IsKeyDown(Keys::Down) && racquetRed->GetY() > -0.8f)
        racquetRed->SetY(racquetRed->GetY() - DeltaTime * racquetRed->Speed);

    Game::Update();
}

Lab2::Lab2() : Game(L"MyGame", 800, 800)
{
    srand(static_cast<unsigned>(time(nullptr)));
    racquetBlue = new RacquetComponent(this, SimpleMath::Vector3(0.0f, 0.0f, 1.0f));
    racquetBlue->SetX(-0.9f);
    racquetRed = new RacquetComponent(this, SimpleMath::Vector3(1.0f, 0.0f, 0.0f));
    racquetRed->SetX(0.9f);
    ball = new BallComponent(this);
    Components.push_back(racquetBlue);
    Components.push_back(racquetRed);
    Components.push_back(ball);
    state = PONG_STATE_COOLDOWN;
    ContinueTime = std::chrono::steady_clock::now() + std::chrono::seconds(1);
    ballHits = 0;
}

void Lab2::Draw()
{
    Game::Draw();

    boolean isGameOver = false;

    std::wstring scoreBlue = std::to_wstring(s1) + L"        ";
    std::wstring scoreRed = std::to_wstring(s2);

    if (state == PONG_STATE_GAMEOVER)
    {
        if (s1 > 5)
            scoreBlue = L"P1 WON";
        else
            scoreBlue = L"P2 WON";
        isGameOver = true;
    }
    ID2D1SolidColorBrush* blueBrush;
    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Blue, 1.0f), &blueBrush);
    ID2D1SolidColorBrush* redBrush;
    D2DRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Red, 1.0f), &redBrush);
    D2DRenderTarget->BeginDraw();
    int x = -100;
    if (!isGameOver)
    {
        D2DRenderTarget->DrawText(
            scoreRed.c_str(),
            scoreRed.length(),
            DWTextFormat,
            D2D1::RectF(100, -700, 800, 800),
            redBrush
        );
    }
    else
    {
        x = 0;
    }
    D2DRenderTarget->DrawText(
        scoreBlue.c_str(),
        scoreBlue.length(),
        DWTextFormat,
        D2D1::RectF(x, -700, 800, 800),
        blueBrush
    );
    
    D2DRenderTarget->EndDraw();
}

void Lab2::Initialize()
{
    Game::Initialize();

    static const WCHAR msc_fontName[] = L"Verdana";
    static const FLOAT msc_fontSize = 50;
    HRESULT hr;

    // Create a Direct2D factory.
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);

    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite factory.
        hr = DWriteCreateFactory(
            DWRITE_FACTORY_TYPE_SHARED,
            __uuidof(DWFactory),
            reinterpret_cast<IUnknown**>(&DWFactory)
        );
    }
    if (SUCCEEDED(hr))
    {
        // Create a DirectWrite text format object.
        hr = DWFactory->CreateTextFormat(
            msc_fontName,
            nullptr,
            DWRITE_FONT_WEIGHT_NORMAL,
            DWRITE_FONT_STYLE_NORMAL,
            DWRITE_FONT_STRETCH_NORMAL,
            msc_fontSize,
            L"", //locale
            &DWTextFormat
        );
    }
    if (SUCCEEDED(hr))
    {
        // Center the text horizontally and vertically.
        DWTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);

        DWTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    }

    hr = SwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&D2DBackBuff);

    // Create the DXGI Surface Render Target.
    float dpi = GetDpiForWindow(Display->hWnd);

    D2D1_RENDER_TARGET_PROPERTIES props =
        D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
            0.0f,
            0.0f);

    // Create a Direct2D render target that can draw into the surface in the swap chain

    hr = D2DFactory->CreateDxgiSurfaceRenderTarget(
        D2DBackBuff,
        &props,
        &D2DRenderTarget);

    hr = D2DRenderTarget->CreateSolidColorBrush(
        D2D1::ColorF(D2D1::ColorF::White, 1.0f),
        &D2Dbrush
    );

    hr = D2DFactory->CreateStrokeStyle(
        D2D1::StrokeStyleProperties(
            D2D1_CAP_STYLE_FLAT,
            D2D1_CAP_STYLE_FLAT,
            D2D1_CAP_STYLE_ROUND,
            D2D1_LINE_JOIN_MITER,
            10.0f,
            D2D1_DASH_STYLE_DASH,
            0.0f),
        nullptr,
        0,
        &D2DLineStrokeStyle
    );
}

void Lab2::DestroyResources()
{
    D2DBackBuff->Release();
    D2DFactory->Release();
    DWFactory->Release();
    DWTextFormat->Release();
    D2DRenderTarget->Release();
    D2Dbrush->Release();
    D2DLineStrokeStyle->Release();
    Game::DestroyResources();
}

void Lab2::IncScore(bool p)
{
    if (p)
        s1 += 1;
    else
        s2 += 1;
    if (s1 > 5 || s2 > 5)
        state = PONG_STATE_GAMEOVER;
}
