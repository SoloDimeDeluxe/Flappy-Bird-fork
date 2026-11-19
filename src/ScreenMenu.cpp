#include "ScreenMenu.h"

#include "Button.h"
#include "ScreenManager.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 110.0f;
	static const float TITLE_POSITION_Y = 50.0f;
	static const Vector2 VERSION_POSITION = { 1200.0f, 670.0f };
	static const float VERSION_FONT_SIZE = 40.0f;
	static const float VERSION_SPACING = 1.0f;

	void MenuUpdate()
	{
		MenuButtonsUpdate();
	}

	void MenuDraw(Font font)
	{
		DrawTextEx(font, "v1.0", VERSION_POSITION, VERSION_FONT_SIZE, VERSION_SPACING, BLACK);
		DrawCenteredText(font, "FLAPPY BIRD", TITLE_POSITION_Y, TITLE_FONT_SIZE, ORANGE);

		ButtonDraw();
		ButtonTextDraw(font);
	}
}
