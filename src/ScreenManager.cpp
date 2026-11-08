#include "ScreenManager.h"
#include "raylib.h"
#include "Player.h"
#include "Obstacle.h"
#include "Button.h"
#include "ScreenMenu.h"
#include "ScreenCredits.h"
#include "ScreenExit.h"
#include "Parallax.h"

namespace rd
{
	Screen currentScreen = Screen::Menu;

	void Update(float delta, bool& gameIsRunning)
	{
		switch (currentScreen)
		{
		case Screen::Menu:
			MenuInit();
			ParallaxInit();
			break;
		case Screen::Play:
			ObstacleUpdate(delta);
			ParallaxUpdate(delta);
			PlayerUpdate(delta);
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
			PlayerDraw();
			ObstacleDraw();
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
			break;
		default:
			break;
		}

		EndDrawing();
	}
}