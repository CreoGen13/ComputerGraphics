#pragma once
#include "Game.h"
#include "RacquetComponent.h"
#include "BallComponent.h"
#include <d2d1.h>
#include <dwrite.h>

#define RIGHT_BOT

enum GameState
{
	PONG_STATE_NORMAL,
	PONG_STATE_COOLDOWN,
	PONG_STATE_GAMEOVER
};

class Lab2 : public Game
{
protected:
	void Update() override;
	unsigned s1;
	unsigned s2;
	ID2D1Factory* D2DFactory;
	IDWriteFactory* DWFactory;
	IDWriteTextFormat* DWTextFormat;
	ID2D1RenderTarget* D2DRenderTarget;
	ID2D1SolidColorBrush* D2Dbrush;
	ID2D1StrokeStyle* D2DLineStrokeStyle;
	IDXGISurface* D2DBackBuff;
public:
	std::chrono::steady_clock::time_point ContinueTime;
	unsigned ballHits;
	RacquetComponent* racquetBlue;
	RacquetComponent* racquetRed;
	BallComponent* ball;
	GameState state;
	Lab2();
	void Draw() override;
	void Initialize() override;
	void DestroyResources() override;
	void IncScore(bool p);
};
