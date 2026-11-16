#include "ScreenMenu.h"

#include "Button.h"
#include "ScreenManager.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 110.0f;
	static const float TITLE_POSITION_Y = 70.0f;
	static const float HOW_TO_PLAY_FONT_SIZE = 28.0f;
	static const float HOW_TO_PLAY_POSITION_Y = 630.0f;
	static const Vector2 VERSION_POSITION = { 1200.0f, 670.0f };
	static const float VERSION_FONT_SIZE = 40.0f;
	static const float VERSION_SPACING = 1.0f;

	void MenuInit()
	{
		ButtonInit();
		IsMousePressed();
	}

	void MenuDraw(Font font)
	{
		DrawTextEx(font, "v1.0", VERSION_POSITION, VERSION_FONT_SIZE, VERSION_SPACING, BLACK);
		DrawCenteredText(font, "FLAPPY BIRD", TITLE_POSITION_Y, TITLE_FONT_SIZE, ORANGE);

		ButtonDraw();
		ButtonTextDraw(font);

		DrawCenteredText(font, "PASS BETWEEN THE PIPES TO SCORE. IN 2 PLAYERS MODE, MOST POINTS WINS!",
			HOW_TO_PLAY_POSITION_Y, HOW_TO_PLAY_FONT_SIZE, DARKGRAY);
	}
}
