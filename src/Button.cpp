#include "Button.h"

#include "ScreenManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "GameAudio.h"

namespace rd
{
	static const float MENU_BUTTON_WIDTH = 280.0f;
	static const float MENU_BUTTON_HEIGHT = 80.0f;
	static const float MENU_BUTTON_FONT_SIZE = 60.0f;
	static const float MENU_BUTTON_SPACING = 2.0f;
	static const float FIRST_MENU_BUTTON_POSITION_Y = 195.0f;

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
		ButtonSetup(play, FIRST_MENU_BUTTON_POSITION_Y);
		ButtonSetup(playTwo, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION);
		ButtonSetup(rules, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 2);
		ButtonSetup(credits, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 3);
		ButtonSetup(exit, FIRST_MENU_BUTTON_POSITION_Y + MENU_BUTTON_SEPARATION * 4);

		back.position.x = 0;
		back.position.y = 0;
		back.size.x = BACK_BUTTON_SIZE;
		back.size.y = BACK_BUTTON_SIZE;
	}

	void ButtonSetup(Button& button, float positionY)
	{
		button.position.x = MENU_BUTTON_POSITION_X;
		button.position.y = positionY;
		button.size.y = MENU_BUTTON_HEIGHT; //height
		button.size.x = MENU_BUTTON_WIDTH; //width
		button.fontSize = MENU_BUTTON_FONT_SIZE;
		button.spacing = MENU_BUTTON_SPACING;
	}

	bool IsMouseOverButton(const Button& button)
	{
		//SE ARMA EL RECTANGULO DEL BOTON PARA USAR LA COLISION QUE YA TRAE RAYLIB
		Rectangle buttonRectangle = { button.position.x, button.position.y, button.size.x, button.size.y };

		return CheckCollisionPointRec(GetMousePosition(), buttonRectangle);
	}

	void IsMousePressed()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (IsMouseOverButton(play))
			{
				//REINICIA LA PARTIDA CADA VEZ QUE SE ENTRA A JUGAR
				PlaySound(gameAudio.click);
				isTwoPlayers = false;
				PlayerInit();
				ObstacleInit();
				CountdownStart(); //CUENTA REGRESIVA SOLO AL ENTRAR DESDE EL MENU
				currentScreen = Screen::Play;
			}
			else if (IsMouseOverButton(playTwo))
			{
				//MODO 2 JUGADORES (SE SETEA ANTES DEL INIT PORQUE EL INIT LO USA)
				PlaySound(gameAudio.click);
				isTwoPlayers = true;
				PlayerInit();
				ObstacleInit();
				CountdownStart(); //CUENTA REGRESIVA SOLO AL ENTRAR DESDE EL MENU
				currentScreen = Screen::Play;
			}
			else if (IsMouseOverButton(rules))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Rules;
			}
			else if (IsMouseOverButton(credits))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Credits;
			}
			else if (IsMouseOverButton(exit))
			{
				currentScreen = Screen::Exit;
			}
		}
	}

	void IsMousePressingBackButton()
	{
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			if (IsMouseOverButton(back))
			{
				PlaySound(gameAudio.click);
				currentScreen = Screen::Menu;
			}
		}
	}

	void BackButtonDraw()
	{
		DrawRectangleV(back.position, back.size, ORANGE);

		if (IsMouseOverButton(back))
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
		//DIBUJO BOTONES
		DrawRectangleV(play.position, play.size, ORANGE);
		DrawRectangleV(playTwo.position, playTwo.size, ORANGE);
		DrawRectangleV(rules.position, rules.size, ORANGE);
		DrawRectangleV(credits.position, credits.size, ORANGE);
		DrawRectangleV(exit.position, exit.size, ORANGE);

		if (IsMouseOverButton(play))
		{
			DrawRectangleV(play.position, play.size, YELLOW);
		}
		else if (IsMouseOverButton(playTwo))
		{
			DrawRectangleV(playTwo.position, playTwo.size, YELLOW);
		}
		else if (IsMouseOverButton(rules))
		{
			DrawRectangleV(rules.position, rules.size, YELLOW);
		}
		else if (IsMouseOverButton(credits))
		{
			DrawRectangleV(credits.position, credits.size, YELLOW);
		}
		else if (IsMouseOverButton(exit))
		{
			DrawRectangleV(exit.position, exit.size, YELLOW);
		}
	}

	void ButtonTextDraw(Font font)
	{
		ButtonLabelDraw(font, play, "1 PLAYER");
		ButtonLabelDraw(font, playTwo, "2 PLAYERS");
		ButtonLabelDraw(font, rules, "RULES");
		ButtonLabelDraw(font, credits, "CREDITS");
		ButtonLabelDraw(font, exit, "EXIT");
	}

	void ButtonLabelDraw(Font font, const Button& button, const char* text)
	{
		//SE MIDE EL TEXTO PARA CENTRARLO EN EL BOTON, ASI NO HACE FALTA UN OFFSET A MANO POR CADA BOTON
		Vector2 textSize = MeasureTextEx(font, text, button.fontSize, button.spacing);
		Vector2 textPosition = { button.position.x + (button.size.x - textSize.x) / 2,
			button.position.y + (button.size.y - textSize.y) / 2 };

		DrawTextEx(font, text, textPosition, button.fontSize, button.spacing, WHITE);
	}
}
