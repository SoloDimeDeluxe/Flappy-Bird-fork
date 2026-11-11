#pragma once
#include "raylib.h"
#include "Button.h"

namespace rd
{
	extern Button continueGame;
	extern Button backToMenu;
	extern Vector2 gameOverTextPosition;

	void GameOverInit();
	void GameOverDraw(Font font);
}