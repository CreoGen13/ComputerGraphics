#pragma once
#include "Game.h"

class Lab1 : public Game
{
protected:
	void Draw() override;
public:
	Lab1(LPCWSTR name, int screenWidth, int screenHeight);
	~Lab1();
};

