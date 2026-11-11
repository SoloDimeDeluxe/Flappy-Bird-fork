#include "ScreenManager.h"
#include <cmath>
#include "RunGame.h"
#include "raylib.h"
#include "Player.h"
#include "Obstacle.h"
#include "Button.h"
#include "ScreenMenu.h"
#include "ScreenCredits.h"
#include "ScreenExit.h"
#include "Parallax.h"
#include "ScreenGameOver.h"

namespace rd
{
	Screen currentScreen = Screen::Menu;
	float startDelay = 0.0f;

	void Update(float delta, bool& gameIsRunning)
	{
		switch (currentScreen)
		{
		case Screen::Menu:
			MenuInit();
			ParallaxInit();
			break;
		case Screen::Play:
			ParallaxUpdate(delta);

			//CUENTA REGRESIVA ANTES DE EMPEZAR A JUGAR
			if (startDelay > 0.0f)
			{
				startDelay -= delta;
			}
			else
			{
				ObstacleUpdate(delta);
				PlayerUpdate(delta);
			}

			IsMousePressingBackButton(); //VOLVER AL MENU
			break;
		case Screen::Rules:
			break;
		case Screen::Settings:
			break;
		case Screen::Credits:
			CreditsInit();
			break;
		case Screen::Exit:
			ExitUpdate(gameIsRunning);
			break;
		case Screen::Pause:
			break;
		case Screen::GameOver:
			GameOverInit();
			break;
		default:
			break;
		}
	}

	void Draw(Font font, Texture2D foreground, Texture2D middleGround, Texture2D background)
	{
		BeginDrawing();

		switch (currentScreen)
		{
		case Screen::Menu:
			MenuDraw(font);
			break;
		case Screen::Play:
			ParallaxDraw(foreground, middleGround, background);
			PlayerDraw(font);
			ObstacleDraw();
			PlayerControlsDraw(font); //DESPUES DE LOS CANIOS PARA QUE NO LOS TAPEN

			if (startDelay > 0.0f)
			{
				CountdownDraw(font);
			}

			BackButtonDraw(); //SE DIBUJA ULTIMO PARA QUE QUEDE ARRIBA DE TODO
			break;
		case Screen::Rules:
			break;
		case Screen::Settings:
			break;
		case Screen::Credits:
			CreditsDraw(font);
			break;
		case Screen::Exit:
			break;
		case Screen::Pause:
			break;
		case Screen::GameOver:
			//SE DIBUJA EL JUEGO QUIETO DE FONDO Y EL CARTEL ENCIMA
			ParallaxDraw(foreground, middleGround, background);
			ObstacleDraw();
			GameOverDraw(font);
			break;
		default:
			break;
		}

		EndDrawing();
	}

	void CountdownDraw(Font font)
	{
		//NUMERO DE LA CUENTA (3, 2, 1) CENTRADO EN LA PANTALLA
		const char* countdownText = TextFormat("%i", static_cast<int>(ceilf(startDelay)));
		Vector2 textSize = MeasureTextEx(font, countdownText, 150, 2);

		DrawTextEx(font, countdownText, { (WINDOW_WIDTH - textSize.x) / 2, (WINDOW_HEIGHT - textSize.y) / 2 },
			150, 2, BLACK);
	}
}