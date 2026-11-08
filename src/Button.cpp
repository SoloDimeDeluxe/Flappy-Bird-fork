#include "Button.h"
#include "ScreenManager.h"
#include "raylib.h"
#include "Player.h"
#include "Obstacle.h"

namespace rd
{
	Button play;
	Button credits;
	Button exit;
	Button back;

	void ButtonInit()
	{
		play.position.x = 530;
		play.position.y = 280;
		play.textPosition.x = 610;
		play.textPosition.y = 295;
		play.textSize = 40;
		play.size.y = 80; //height
		play.size.x = 280; //width
		play.fontSize = 60;
		play.spacing = 2;

		credits.position.x = 530;
		credits.position.y = 380;
		credits.textPosition.x = 575;
		credits.textPosition.y = 395;
		credits.textSize = 40;
		credits.size.y = 80;
		credits.size.x = 280;
		credits.fontSize = 60;
		credits.spacing = 2;

		exit.position.x = 530;
		exit.position.y = 480;
		exit.textPosition.x = 620;
		exit.textPosition.y = 495;
		exit.textSize = 40;
		exit.size.y = 80;
		exit.size.x = 280;
		exit.fontSize = 60;
		exit.spacing = 2;

		back.position.x = 0;
		back.position.y = 0;
		back.size.y = 70;
		back.size.x = 70;
		back.textPosition.x = -40;
		back.textPosition.y = -20;
		back.textSize = 20;
		back.fontSize = 30;
		back.spacing = 2;
	}

	bool CheckCollisionMouseButton(Vector2 mousePosition, float buttonX, 
		float buttonY, float buttonHeight, float buttonWidth)
	{
		return buttonX <= mousePosition.x && buttonX + buttonWidth >= mousePosition.x
			&& mousePosition.y >= buttonY && mousePosition.y <= buttonY + buttonHeight;
	}

	void IsMousePressingBackButton()
	{
		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionMouseButton(mousePosition, back.position.x, back.position.y, back.size.y, back.size.x))
			{
				currentScreen = Screen::Menu;
			}
		}
	}

	void IsMousePressed()
	{
		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionMouseButton(mousePosition, play.position.x, 
				play.position.y, play.size.y, play.size.x))
			{
				//REINICIA LA PARTIDA CADA VEZ QUE SE ENTRA A JUGAR
				PlayerInit();
				ObstacleInit();
				currentScreen = Screen::Play;
			}
			else if (CheckCollisionMouseButton(mousePosition, credits.position.x, 
				credits.position.y, credits.size.y, credits.size.x))
			{
				currentScreen = Screen::Credits;
			}
			else if (CheckCollisionMouseButton(mousePosition, exit.position.x, exit.position.y, exit.size.y, exit.size.x))
			{
				currentScreen = Screen::Exit;
			}
		}
	}

	void BackButtonDraw()
	{
		Vector2 mousePosition = GetMousePosition();

		DrawRectangleV(back.position, back.size, ORANGE);

		if (CheckCollisionMouseButton(mousePosition, back.position.x, back.position.y, back.size.y, back.size.x))
		{
			DrawRectangleV(back.position, back.size, YELLOW);
		}
	}

	void ButtonDraw()
	{
		Vector2 mousePosition = GetMousePosition();

		//DIBUJO BOTONES
		DrawRectangleV(play.position, play.size, ORANGE);
		DrawRectangleV(credits.position, credits.size, ORANGE);
		DrawRectangleV(exit.position, exit.size, ORANGE);

		if (CheckCollisionMouseButton(mousePosition, play.position.x, 
			play.position.y, play.size.y, play.size.x))
		{
			DrawRectangleV(play.position, play.size, YELLOW);
		}
		else if (CheckCollisionMouseButton(mousePosition, credits.position.x, 
			credits.position.y, credits.size.y, credits.size.x))
		{
			DrawRectangleV(credits.position, credits.size, YELLOW);
		}
		else if (CheckCollisionMouseButton(mousePosition, exit.position.x,
			exit.position.y, exit.size.y, exit.size.x))
		{
			DrawRectangleV(exit.position, exit.size, YELLOW);
		}
	}

	void ButtonTextDraw(Font font)
	{
		DrawTextEx(font, "PLAY", play.textPosition, play.fontSize, play.spacing, WHITE);
		DrawTextEx(font, "CREDITS", credits.textPosition, credits.fontSize, credits.spacing, WHITE);
		DrawTextEx(font, "EXIT", exit.textPosition, exit.fontSize, exit.spacing, WHITE);
	}
}