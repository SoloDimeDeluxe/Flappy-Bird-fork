#include "ScreenRules.h"

#include "Button.h"
#include "ScreenManager.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 70.0f;
	static const float TITLE_POSITION_Y = 20.0f;
	static const float SECTION_FONT_SIZE = 36.0f;
	static const float LINE_FONT_SIZE = 26.0f;
	static const float FIRST_SECTION_POSITION_Y = 105.0f;
	static const float SECTION_TITLE_HEIGHT = 38.0f; //ESPACIO ENTRE EL TITULO DE LA SECCION Y SU PRIMERA LINEA
	static const float LINE_HEIGHT = 29.0f;
	static const float SECTION_SEPARATION = 15.0f;

	static const int HOW_TO_PLAY_LINES_AMOUNT = 3;
	static const int CONTROLS_LINES_AMOUNT = 2;
	static const int TWO_PLAYERS_LINES_AMOUNT = 3;
	static const int DIFFICULTY_LINES_AMOUNT = 1;
	static const int POWER_UPS_LINES_AMOUNT = 2;

	static const char* HOW_TO_PLAY_LINES[HOW_TO_PLAY_LINES_AMOUNT] =
	{
		"Fly between the pipes without touching them or falling to the ground",
		"Every pipe you pass gives you 1 point",
		"Pass close to the edge of the gap for extra points: +1 CLOSE, +2 PERFECT"
	};

	static const char* CONTROLS_LINES[CONTROLS_LINES_AMOUNT] =
	{
		"Jump: SPACE (player 1) - UP ARROW (player 2)",
		"Pause: P or ESC"
	};

	static const char* TWO_PLAYERS_LINES[TWO_PLAYERS_LINES_AMOUNT] =
	{
		"Both birds fly at the same time. Each one has 3 lives",
		"After losing a life you blink and can't crash for 2 seconds",
		"Most points wins. If it's a tie, the one who survived longer wins"
	};

	static const char* DIFFICULTY_LINES[DIFFICULTY_LINES_AMOUNT] =
	{
		"At 10 points the pipes go faster and some have two gaps"
	};

	static const char* POWER_UPS_LINES[POWER_UPS_LINES_AMOUNT] =
	{
		"In 2 players mode some pipes bring a power-up. Fly through it to grab it",
		"x2 POINTS (yellow): every point you get counts double for 6 seconds"
	};

	static float SectionDraw(Font font, const char* title, const char* lines[], int linesAmount, float positionY);

	void RulesInit()
	{
		IsMousePressingBackButton();
	}

	void RulesDraw(Font font)
	{
		BackButtonDraw();

		DrawCenteredText(font, "RULES", TITLE_POSITION_Y, TITLE_FONT_SIZE, BLACK);

		//CADA SECCION DEVUELVE DONDE TERMINA, ASI LA SIGUIENTE VA ABAJO
		float positionY = FIRST_SECTION_POSITION_Y;
		positionY = SectionDraw(font, "HOW TO PLAY", HOW_TO_PLAY_LINES, HOW_TO_PLAY_LINES_AMOUNT, positionY);
		positionY = SectionDraw(font, "CONTROLS", CONTROLS_LINES, CONTROLS_LINES_AMOUNT, positionY);
		positionY = SectionDraw(font, "2 PLAYERS MODE", TWO_PLAYERS_LINES, TWO_PLAYERS_LINES_AMOUNT, positionY);
		positionY = SectionDraw(font, "DIFFICULTY", DIFFICULTY_LINES, DIFFICULTY_LINES_AMOUNT, positionY);
		SectionDraw(font, "POWER-UPS", POWER_UPS_LINES, POWER_UPS_LINES_AMOUNT, positionY);
	}

	static float SectionDraw(Font font, const char* title, const char* lines[], int linesAmount, float positionY)
	{
		DrawCenteredText(font, title, positionY, SECTION_FONT_SIZE, ORANGE);
		positionY += SECTION_TITLE_HEIGHT;

		for (int i = 0; i < linesAmount; i++)
		{
			DrawCenteredText(font, lines[i], positionY, LINE_FONT_SIZE, BLACK);
			positionY += LINE_HEIGHT;
		}

		return positionY + SECTION_SEPARATION;
	}
}
