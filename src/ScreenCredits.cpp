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
	static const int CREDITS_LINES_AMOUNT = 11;

	//TEXTO, ALTURA, TAMANIO Y COLOR DE CADA LINEA
	static const Credits CREDITS_LINES[CREDITS_LINES_AMOUNT] =
	{
		{ "CREDITS", 30.0f, TITLE_FONT_SIZE, BLACK },
		{ "GAME DEVELOPMENT", 140.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Mercedes Ramirez Diaz (original author)", 185.0f, NAME_FONT_SIZE, BLACK },
		{ "Valentin Reyes Cuadra (fork: 2 players, score, pause, audio)", 225.0f, NAME_FONT_SIZE, BLACK },
		{ "ART & FONT", 295.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Parallax backgrounds generated with ChatGPT", 340.0f, NAME_FONT_SIZE, BLACK },
		{ "Muro Slant font by Joan Alegret (La Tipomatica)", 380.0f, NAME_FONT_SIZE, BLACK },
		{ "MUSIC & SOUND EFFECTS", 450.0f, SECTION_FONT_SIZE, ORANGE },
		{ "Chiptune music and effects synthesized by code (see res_raw/audio)", 495.0f, NAME_FONT_SIZE, BLACK },
		{ "MADE WITH", 565.0f, SECTION_FONT_SIZE, ORANGE },
		{ "raylib 6.2 - www.raylib.com", 610.0f, NAME_FONT_SIZE, BLACK }
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
