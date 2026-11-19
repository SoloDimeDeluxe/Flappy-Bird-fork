#include "ScreenManager.h"

#include <cmath>

#include "RunGame.h"
#include "Player.h"
#include "Obstacle.h"
#include "Button.h"
#include "ScreenMenu.h"
#include "ScreenCredits.h"
#include "ScreenRules.h"
#include "ScreenExit.h"
#include "Parallax.h"
#include "ScreenGameOver.h"
#include "ScreenPause.h"
#include "GameAudio.h"

namespace rd
{
	static const float START_DELAY = 3.0f; //SEGUNDOS
	static const float COUNTDOWN_FONT_SIZE = 150.0f;
	static const float TEXT_SPACING = 2.0f;

	Screen currentScreen = Screen::Menu;

	static float startDelay = 0.0f;

	static void CountdownDraw(Font font);

	void CountdownStart()
	{
		startDelay = START_DELAY;
		PlaySound(gameAudio.countdown);
	}

	void Update(float delta, bool& gameIsRunning)
	{
		switch (currentScreen)
		{
		case Screen::Menu:
			MenuUpdate();
			break;
		case Screen::Play:
			ParallaxUpdate(delta);

			//CUENTA REGRESIVA ANTES DE EMPEZAR A JUGAR
			if (startDelay > 0.0f)
			{
				int previousNumber = static_cast<int>(ceilf(startDelay));
				startDelay -= delta;
				int currentNumber = static_cast<int>(ceilf(startDelay));

				//BEEP CADA VEZ QUE CAMBIA EL NUMERO
				if (currentNumber != previousNumber && currentNumber > 0)
				{
					PlaySound(gameAudio.countdown);
				}
			}
			else
			{
				//LA DIFICULTAD SUBE SEGUN EL QUE VA GANANDO
				int highestScore = bird.score > birdTwo.score ? bird.score : birdTwo.score;
				ObstacleUpdate(delta, highestScore);
				PlayerUpdate(delta);
			}

			BackButtonUpdate(); //VOLVER AL MENU
			PauseCheckInput();
			break;
		case Screen::Rules:
			RulesUpdate();
			break;
		case Screen::Credits:
			CreditsUpdate();
			break;
		case Screen::Exit:
			ExitUpdate(gameIsRunning);
			break;
		case Screen::Pause:
			PauseUpdate();
			break;
		case Screen::GameOver:
			GameOverUpdate(delta);
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
			PlayerScoreDraw(font);
			PauseHintDraw(font);
			DifficultyWarningDraw(font);

			if (startDelay > 0.0f)
			{
				CountdownDraw(font);
			}

			BackButtonDraw(); //SE DIBUJA ULTIMO PARA QUE QUEDE ARRIBA DE TODO
			break;
		case Screen::Rules:
			RulesDraw(font);
			break;
		case Screen::Credits:
			CreditsDraw(font);
			break;
		case Screen::Exit:
			break;
		case Screen::Pause:
			//JUEGO QUIETO DE FONDO Y EL CARTEL DE PAUSA ENCIMA
			ParallaxDraw(foreground, middleGround, background);
			PlayerDraw(font);
			ObstacleDraw();
			PlayerScoreDraw(font);
			PauseDraw(font);
			BackButtonDraw();
			break;
		case Screen::GameOver:
			//SE DIBUJA EL JUEGO QUIETO DE FONDO Y EL CARTEL ENCIMA
			ParallaxDraw(foreground, middleGround, background);
			PlayerDraw(font);
			ObstacleDraw();
			GameOverDraw(font);
			break;
		default:
			break;
		}

		EndDrawing();
	}

	void DrawCenteredText(Font font, const char* text, float positionY, float fontSize, Color color)
	{
		Vector2 textSize = MeasureTextEx(font, text, fontSize, TEXT_SPACING);
		DrawTextEx(font, text, { (WINDOW_WIDTH - textSize.x) / 2, positionY }, fontSize, TEXT_SPACING, color);
	}

	static void CountdownDraw(Font font)
	{
		DrawCenteredText(font, TextFormat("%i", static_cast<int>(ceilf(startDelay))),
			(WINDOW_HEIGHT - COUNTDOWN_FONT_SIZE) / 2, COUNTDOWN_FONT_SIZE, BLACK);
	}
}