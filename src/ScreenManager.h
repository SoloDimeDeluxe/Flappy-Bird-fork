#pragma once
#include "raylib.h"

namespace rd
{
	enum class Screen
	{
		Menu = 0,
		Play,
		Rules,
		Settings,
		Credits,
		Exit,
		Pause,
		GameOver
	};

	extern Screen currentScreen;

	const float START_DELAY = 3.0f;
	extern float startDelay;

	void Update(float delta, bool& gameIsRunning);
	void Draw(Font font, Texture2D foreground, 
		Texture2D middleGround, Texture2D background);
	void CountdownDraw(Font font);
}