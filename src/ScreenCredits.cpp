#include "ScreenCredits.h"

#include "Button.h"
#include "ScreenManager.h"

namespace rd
{
	struct Credits
	{
		const char* text;
		float positionY;
		float fontSize;
		Color color;
	};

	static const float TITLE_FONT_SIZE = 80.0f;
	static const float SECTION_FONT_SIZE = 40.0f;
	static const float NAME_FONT_SIZE = 34.0f;
	static const int CREDITS_LINES_AMOUNT = 10;

	//TEXTO, ALTURA, TAMANIO Y COLOR DE CADA LINEA
	static const Credits CREDITS_LINES[CREDITS_LINES_AMOUNT] =
	{
		{ "CREDITS", 30.0f, TITLE_FONT_SIZE, BLACK },
		{ "GAME DEVELOPMENT", 140.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Mercedes Ramirez Diaz (original author)", 185.0f, NAME_FONT_SIZE, BLACK },
		{ "Valentin Reyes Cuadra (fork: 2 players, score, pause, audio)", 225.0f, NAME_FONT_SIZE, BLACK },
		{ "ART & FONT", 300.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Parallax backgrounds and Muroslant font: from the original project", 345.0f, NAME_FONT_SIZE, BLACK },
		{ "MUSIC & SOUND EFFECTS", 420.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Chiptune music and effects synthesized by code (see res_raw/audio)", 465.0f, NAME_FONT_SIZE, BLACK },
		{ "MADE WITH", 540.0f, SECTION_FONT_SIZE, ORANGE },
		{ "raylib 6.2 - www.raylib.com", 585.0f, NAME_FONT_SIZE, BLACK }
	};

	void CreditsInit()
	{
		IsMousePressingBackButton();
	}

	void CreditsDraw(Font font)
	{
		BackButtonDraw();

		for (int i = 0; i < CREDITS_LINES_AMOUNT; i++)
		{
			DrawCenteredText(font, CREDITS_LINES[i].text, CREDITS_LINES[i].positionY,
				CREDITS_LINES[i].fontSize, CREDITS_LINES[i].color);
		}
	}
}
