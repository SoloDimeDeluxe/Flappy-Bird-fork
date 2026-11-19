#pragma once

#include "raylib.h"

namespace rd
{
	enum class Screen
	{
		Menu = 0,
		Play,
		Rules,
		Credits,
		Exit,
		Pause,
		GameOver
	};

	extern Screen currentScreen;

	void CountdownStart();
	void Update(float delta, bool& gameIsRunning);
	void Draw(Font font, Texture2D foreground,
		Texture2D middleGround, Texture2D background);
	void DrawCenteredText(Font font, const char* text, float positionY, float fontSize, Color color);
}