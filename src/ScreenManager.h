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

	void Update(float delta, bool& gameIsRunning);
	void Draw(Font font, Texture2D foreground, 
		Texture2D middleGround, Texture2D background);
}