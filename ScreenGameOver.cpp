#include "ScreenGameOver.h"
#include "raylib.h"
#include "ScreenManager.h"
#include "RunGame.h"
#include "Player.h"
#include "Obstacle.h"

namespace rd
{
	Button continueGame;
	Button backToMenu;
	Vector2 gameOverTextPosition;

	void GameOverInit()
	{
		gameOverTextPosition.x = 448;
		gameOverTextPosition.y = 180;

		continueGame.position.x = 530;
		continueGame.position.y = 330;
		continueGame.textPosition.x = 550;
		continueGame.textPosition.y = 345;
		continueGame.textSize = 40;
		continueGame.size.y = 80;
		continueGame.size.x = 280;
		continueGame.fontSize = 60;
		continueGame.spacing = 2;

		backToMenu.position.x = 530;
		backToMenu.position.y = 430;
		backToMenu.textPosition.x = 606;
		backToMenu.textPosition.y = 445;
		backToMenu.textSize = 40;
		backToMenu.size.y = 80;
		backToMenu.size.x = 280;
		backToMenu.fontSize = 60;
		backToMenu.spacing = 2;

		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionMouseButton(mousePosition, continueGame.position.x,
				continueGame.position.y, continueGame.size.y, continueGame.size.x))
			{
				//SE REINICIA LA PARTIDA EN EL MISMO MODO (1 O 2 JUGADORES)
				PlayerInit();
				ObstacleInit();
				currentScreen = Screen::Play;
			}
			else if (CheckCollisionMouseButton(mousePosition, backToMenu.position.x,
				backToMenu.position.y, backToMenu.size.y, backToMenu.size.x))
			{
				currentScreen = Screen::Menu;
			}
		}
	}

	void GameOverDraw(Font font)
	{
		Vector2 mousePosition = GetMousePosition();

		//FONDO OSCURO TRANSPARENTE ARRIBA DEL JUEGO CONGELADO
		DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, Fade(BLACK, 0.6f));

		DrawTextEx(font, "GAME OVER", gameOverTextPosition, 100, 2, WHITE);

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
}