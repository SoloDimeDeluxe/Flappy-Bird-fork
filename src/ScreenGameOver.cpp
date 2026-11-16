#include "ScreenGameOver.h"

#include "ScreenManager.h"
#include "RunGame.h"
#include "Player.h"
#include "Obstacle.h"
#include "Button.h"
#include "GameAudio.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 100.0f;
	static const float RESULT_FONT_SIZE = 45.0f;
	static const float TITLE_POSITION_Y = 150.0f;
	static const float RESULT_LINE_ONE_Y = 260.0f;
	static const float RESULT_LINE_TWO_Y = 310.0f;
	static const float GAME_OVER_DELAY = 1.0f; //SEGUNDOS ANTES DE MOSTRAR EL CARTEL
	static const float BACKGROUND_ALPHA = 0.6f;
	static const float CONTINUE_BUTTON_POSITION_Y = 380.0f;
	static const float CONTINUE_TEXT_OFFSET_X = 20.0f;
	static const float BACK_TO_MENU_TEXT_OFFSET_X = 76.0f;

	static float gameOverTimer = 0.0f;

	static Button continueGame;
	static Button backToMenu;

	static void ResultDraw(Font font);

	void GameOverStart()
	{
		gameOverTimer = GAME_OVER_DELAY;
		currentScreen = Screen::GameOver;
		PlaySound(gameAudio.gameOver);
	}

	void GameOverInit(float delta)
	{
		if (gameOverTimer > 0.0f)
		{
			gameOverTimer -= delta;
			return;
		}

		ButtonSetup(continueGame, CONTINUE_BUTTON_POSITION_Y, CONTINUE_TEXT_OFFSET_X);
		ButtonSetup(backToMenu, CONTINUE_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION, BACK_TO_MENU_TEXT_OFFSET_X);

		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionMouseButton(mousePosition, continueGame.position.x,
				continueGame.position.y, continueGame.size.y, continueGame.size.x))
			{
				//SE REINICIA LA PARTIDA EN EL MISMO MODO (1 O 2 JUGADORES)
				PlaySound(gameAudio.click);
				PlayerInit();
				ObstacleInit();
				currentScreen = Screen::Play;
			}
			else if (CheckCollisionMouseButton(mousePosition, backToMenu.position.x,
				backToMenu.position.y, backToMenu.size.y, backToMenu.size.x))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Menu;
			}
		}
	}

	void GameOverDraw(Font font)
	{
		if (gameOverTimer > 0.0f)
		{
			return;
		}

		Vector2 mousePosition = GetMousePosition();

		//FONDO OSCURO TRANSPARENTE ARRIBA DEL JUEGO CONGELADO
		DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, BACKGROUND_ALPHA));

		DrawCenteredText(font, "GAME OVER", TITLE_POSITION_Y, TITLE_FONT_SIZE, WHITE);
		ResultDraw(font);

		//DIBUJO BOTONES
		DrawRectangleV(continueGame.position, continueGame.size, ORANGE);
		DrawRectangleV(backToMenu.position, backToMenu.size, ORANGE);

		if (CheckCollisionMouseButton(mousePosition, continueGame.position.x,
			continueGame.position.y, continueGame.size.y, continueGame.size.x))
		{
			DrawRectangleV(continueGame.position, continueGame.size, YELLOW);
		}
		else if (CheckCollisionMouseButton(mousePosition, backToMenu.position.x,
			backToMenu.position.y, backToMenu.size.y, backToMenu.size.x))
		{
			DrawRectangleV(backToMenu.position, backToMenu.size, YELLOW);
		}

		DrawTextEx(font, "CONTINUE", continueGame.textPosition, continueGame.fontSize, continueGame.spacing, WHITE);
		DrawTextEx(font, "MENU", backToMenu.textPosition, backToMenu.fontSize, backToMenu.spacing, WHITE);
	}

	static void ResultDraw(Font font)
	{
		if (isTwoPlayers)
		{
			Winner winner = GetWinner();

			if (winner == Winner::PlayerOne)
			{
				DrawCenteredText(font, "PLAYER 1 WINS!", RESULT_LINE_ONE_Y, RESULT_FONT_SIZE, bird.color);
			}
			else if (winner == Winner::PlayerTwo)
			{
				DrawCenteredText(font, "PLAYER 2 WINS!", RESULT_LINE_ONE_Y, RESULT_FONT_SIZE, birdTwo.color);
			}
			else
			{
				DrawCenteredText(font, "DRAW!", RESULT_LINE_ONE_Y, RESULT_FONT_SIZE, WHITE);
			}

			DrawCenteredText(font, TextFormat("P1: %i     P2: %i", bird.score, birdTwo.score),
				RESULT_LINE_TWO_Y, RESULT_FONT_SIZE, WHITE);
		}
		else
		{
			DrawCenteredText(font, TextFormat("SCORE: %i", bird.score), RESULT_LINE_ONE_Y, RESULT_FONT_SIZE, WHITE);
			DrawCenteredText(font, TextFormat("BEST: %i", bestScore), RESULT_LINE_TWO_Y, RESULT_FONT_SIZE, YELLOW);
		}
	}
}
