#include "ScreenMenu.h"
#include "raylib.h"
#include "Button.h"
#include "Player.h"

namespace rd
{
	void MenuInit()
	{
		ButtonInit();
		IsMousePressed();
	}

	void MenuDraw(Font font)
	{
		DrawTextEx(font, TextFormat("v0.4"), bird.textPosition, bird.fontSize, bird.spacing, BLACK);
		ButtonDraw();
		ButtonTextDraw(font);
	}
}