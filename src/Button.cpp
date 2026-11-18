#include "Button.h"

#include "ScreenManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "GameAudio.h"

namespace rd
{
	static const float MENU_BUTTON_WIDTH = 280.0f;
	static const float MENU_BUTTON_HEIGHT = 80.0f;
	static const float MENU_BUTTON_TEXT_OFFSET_Y = 15.0f;
	static const float MENU_BUTTON_TEXT_SIZE = 40.0f;
	static const float MENU_BUTTON_FONT_SIZE = 60.0f;
	static const float MENU_BUTTON_SPACING = 2.0f;
	static const float FIRST_MENU_BUTTON_POSITION_Y = 195.0f;

	//PARA QUE EL TEXTO QUEDE CENTRADO EN CADA BOTON
	static const float PLAY_TEXT_OFFSET_X = 30.0f;
	static const float PLAY_TWO_TEXT_OFFSET_X = 13.0f;
	static const float RULES_TEXT_OFFSET_X = 70.0f;
	static const float CREDITS_TEXT_OFFSET_X = 45.0f;
	static const float EXIT_TEXT_OFFSET_X = 90.0f;

	static const float BACK_BUTTON_SIZE = 70.0f;
	static const float ARROW_MARGIN = 18.0f;

	static Button play;
	static Button playTwo;
	static Button rules;
	static Button credits;
	static Button exit;
	static Button back;

	void ButtonInit()
	{
		ButtonSetup(play, FIRST_MENU_BUTTON_POSITION_Y, PLAY_TEXT_OFFSET_X);
		ButtonSetup(playTwo, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION, PLAY_TWO_TEXT_OFFSET_X);
		ButtonSetup(rules, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 2, RULES_TEXT_OFFSET_X);
		ButtonSetup(credits, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 3, CREDITS_TEXT_OFFSET_X);
		ButtonSetup(exit, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 4, EXIT_TEXT_OFFSET_X);

		back.position.x = 0;
		back.position.y = 0;
		back.size.x = BACK_BUTTON_SIZE;
		back.size.y = BACK_BUTTON_SIZE;
	}

	void ButtonSetup(Button& button, float positionY, float textOffsetX)
	{
		button.position.x = MENU_BUTTON_POSITION_X;
		button.position.y = positionY;
		button.textPosition.x = MENU_BUTTON_POSITION_X + textOffsetX;
		button.textPosition.y = positionY + MENU_BUTTON_TEXT_OFFSET_Y;
		button.textSize = MENU_BUTTON_TEXT_SIZE;
		button.size.y = MENU_BUTTON_HEIGHT; //height
		button.size.x = MENU_BUTTON_WIDTH; //width
		button.fontSize = MENU_BUTTON_FONT_SIZE;
		button.spacing = MENU_BUTTON_SPACING;
	}

	bool CheckCollisionMouseButton(Vector2 mousePosition, float buttonX,
		float buttonY, float buttonHeight, float buttonWidth)
	{
		return buttonX <= mousePosition.x && buttonX + buttonWidth >= mousePosition.x
			&& mousePosition.y >= buttonY && mousePosition.y <= buttonY + buttonHeight;
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
				PlaySound(gameAudio.click);
				isTwoPlayers = false;
				PlayerInit();
				ObstacleInit();
				CountdownStart(); //CUENTA REGRESIVA SOLO AL ENTRAR DESDE EL MENU
				currentScreen = Screen::Play;
			}
			else if (CheckCollisionMouseButton(mousePosition, playTwo.position.x,
				playTwo.position.y, playTwo.size.y, playTwo.size.x))
			{
				//MODO 2 JUGADORES (SE SETEA ANTES DEL INIT PORQUE EL INIT LO USA)
				PlaySound(gameAudio.click);
				isTwoPlayers = true;
				PlayerInit();
				ObstacleInit();
				CountdownStart(); //CUENTA REGRESIVA SOLO AL ENTRAR DESDE EL MENU
				currentScreen = Screen::Play;
			}
			else if (CheckCollisionMouseButton(mousePosition, rules.position.x,
				rules.position.y, rules.size.y, rules.size.x))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Rules;
			}
			else if (CheckCollisionMouseButton(mousePosition, credits.position.x,
				credits.position.y, credits.size.y, credits.size.x))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Credits;
			}
			else if (CheckCollisionMouseButton(mousePosition, exit.position.x, exit.position.y, exit.size.y, exit.size.x))
			{
				currentScreen = Screen::Exit;
			}
		}
	}

	void IsMousePressingBackButton()
	{
		Vector2 mousePosition = GetMousePosition();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (CheckCollisionMouseButton(mousePosition, back.position.x, back.position.y, back.size.y, back.size.x))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Menu;
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

		//FLECHA (RAYLIB PIDE LOS VERTICES EN SENTIDO ANTIHORARIO)
		Vector2 arrowTop = { back.position.x + back.size.x - ARROW_MARGIN, back.position.y + ARROW_MARGIN };
		Vector2 arrowTip = { back.position.x + ARROW_MARGIN, back.position.y + back.size.y / 2 };
		Vector2 arrowBottom = { back.position.x + back.size.x - ARROW_MARGIN, back.position.y + back.size.y - ARROW_MARGIN };
		DrawTriangle(arrowTop, arrowTip, arrowBottom, WHITE);
	}

	void ButtonDraw()
	{
		Vector2 mousePosition = GetMousePosition();

		//DIBUJO BOTONES
		DrawRectangleV(play.position, play.size, ORANGE);
		DrawRectangleV(playTwo.position, playTwo.size, ORANGE);
		DrawRectangleV(rules.position, rules.size, ORANGE);
		DrawRectangleV(credits.position, credits.size, ORANGE);
		DrawRectangleV(exit.position, exit.size, ORANGE);

		if (CheckCollisionMouseButton(mousePosition, play.position.x,
			play.position.y, play.size.y, play.size.x))
		{
			DrawRectangleV(play.position, play.size, YELLOW);
		}
		else if (CheckCollisionMouseButton(mousePosition, playTwo.position.x,
			playTwo.position.y, playTwo.size.y, playTwo.size.x))
		{
			DrawRectangleV(playTwo.position, playTwo.size, YELLOW);
		}
		else if (CheckCollisionMouseButton(mousePosition, rules.position.x,
			rules.position.y, rules.size.y, rules.size.x))
		{
			DrawRectangleV(rules.position, rules.size, YELLOW);
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
		DrawTextEx(font, "1 PLAYER", play.textPosition, play.fontSize, play.spacing, WHITE);
		DrawTextEx(font, "2 PLAYERS", playTwo.textPosition, playTwo.fontSize, playTwo.spacing, WHITE);
		DrawTextEx(font, "RULES", rules.textPosition, rules.fontSize, rules.spacing, WHITE);
		DrawTextEx(font, "CREDITS", credits.textPosition, credits.fontSize, credits.spacing, WHITE);
		DrawTextEx(font, "EXIT", exit.textPosition, exit.fontSize, exit.spacing, WHITE);
	}
}
