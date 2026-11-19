#include "ScreenPause.h"

#include "RunGame.h"
#include "ScreenManager.h"
#include "Button.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 100.0f;
	static const float TEXT_FONT_SIZE = 40.0f;
	static const float HINT_FONT_SIZE = 25.0f;
	static const float TITLE_POSITION_Y = 230.0f;
	static const float TEXT_POSITION_Y = 360.0f;
	static const float BACK_TEXT_POSITION_Y = 420.0f;
	static const float HINT_POSITION_Y = 45.0f;
	static const float BACKGROUND_ALPHA = 0.6f;

	void PauseCheckInput()
	{
		//LA MISMA TECLA PAUSA Y DESPAUSA
		if (IsKeyPressed(KEY_P) || IsKeyPressed(KEY_ESCAPE))
		{
			if (currentScreen == Screen::Play)
			{
				currentScreen = Screen::Pause;
			}
			else if (currentScreen == Screen::Pause)
			{
				currentScreen = Screen::Play;
			}
		}
	}

	void PauseUpdate()
	{
		PauseCheckInput();
		BackButtonUpdate();
	}

	void PauseDraw(Font font)
	{
		DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, BACKGROUND_ALPHA));

		DrawCenteredText(font, "PAUSED", TITLE_POSITION_Y, TITLE_FONT_SIZE, WHITE);
		DrawCenteredText(font, "PRESS P OR ESC TO RESUME", TEXT_POSITION_Y, TEXT_FONT_SIZE, WHITE);
		DrawCenteredText(font, "OR CLICK THE ARROW TO GO BACK TO THE MENU", BACK_TEXT_POSITION_Y, TEXT_FONT_SIZE, WHITE);
	}

	void PauseHintDraw(Font font)
	{
		DrawCenteredText(font, "P / ESC: PAUSE", HINT_POSITION_Y, HINT_FONT_SIZE, DARKGRAY);
	}
}
