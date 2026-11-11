#include "Player.h"
#include "raylib.h"
#include "RunGame.h"
#include "Obstacle.h"
#include "Collision.h"
#include "ScreenManager.h"

namespace rd
{
	Player bird;
	Player birdTwo;
	bool isTwoPlayers = false;

	void PlayerInit()
	{
		bird.position.x = 200;
		bird.position.y = 400;
		bird.direction.x = 0;
		bird.direction.y = 0;
		bird.size.x = 50;
		bird.size.y = 50;
		bird.rotation = 0;
		bird.radius = 40;
		bird.score = 0;
		bird.velocity = 300.0f;
		bird.jumpForce = -200.0f;
		bird.isAlive = true;
		bird.jumpKey = KEY_SPACE;
		bird.color = ORANGE;

		bird.textPosition.x = 1200;
		bird.textPosition.y = 670; //DENTRO DE LA VENTANA (ALTO 720)
		bird.fontSize = 40;
		bird.spacing = 1;

		//JUGADOR 2: ARRANCA IGUAL QUE EL 1 PERO MAS ARRIBA, CON OTRA TECLA Y OTRO COLOR
		birdTwo = bird;
		birdTwo.position.y = 250;
		birdTwo.jumpKey = KEY_UP;
		birdTwo.color = PURPLE;
		birdTwo.isAlive = isTwoPlayers; //EN MODO 1 JUGADOR NO PARTICIPA
	}

	void PlayerUpdate(float delta)
	{
		if (bird.isAlive)
		{
			PlayerMovement(bird, delta);
		}
		if (birdTwo.isAlive)
		{
			PlayerMovement(birdTwo, delta);
		}

		isPlayerAlive();
	}

	void PlayerMovement(Player& player, float delta)
	{
		if (IsKeyPressed(player.jumpKey))
		{
			player.velocity = player.jumpForce;
		}

		//VELOCITY:
		player.velocity += GRAVITY * delta;
		player.position.y += delta * player.velocity;

		//PISO Y TECHO SEGUN EL TAMANIO DEL RECTANGULO
		if (player.position.y + player.size.y > WINDOW_HEIGHT)
		{
			player.isAlive = false;
			player.position.y = WINDOW_HEIGHT - player.size.y;
		}
		else if (player.position.y < 0)
		{
			player.velocity = 0;
			player.position.y = 0;
		}

		if (CheckRectangleCollision(player.position, player.size, pipeOne.position, pipeOne.size) ||
			CheckRectangleCollision(player.position, player.size, pipeTwo.position, pipeTwo.size))
		{
			player.isAlive = false;
		}
	}

	void PlayerDraw(Font font)
	{
		//SOLO SE DIBUJAN LOS JUGADORES QUE SIGUEN VIVOS
		if (bird.isAlive)
		{
			DrawRectangleV(bird.position, bird.size, bird.color); // x, y, width, height, color
		}

		if (isTwoPlayers)
		{
			//ETIQUETAS ARRIBA DE CADA JUGADOR PARA SABER QUIEN ES QUIEN
			if (bird.isAlive)
			{
				DrawTextEx(font, "P1", { bird.position.x + 12, bird.position.y - 30 }, 30, 1, bird.color);
			}
			if (birdTwo.isAlive)
			{
				DrawRectangleV(birdTwo.position, birdTwo.size, birdTwo.color);
				DrawTextEx(font, "P2", { birdTwo.position.x + 10, birdTwo.position.y - 30 }, 30, 1, birdTwo.color);
			}
		}
	}

	void PlayerControlsDraw(Font font)
	{
		//CONTROLES EN PANTALLA ARRIBA AL CENTRO
		if (isTwoPlayers)
		{
			DrawTextEx(font, "P1: SPACE", { 480, 10 }, 30, 1, bird.color);
			DrawTextEx(font, "P2: UP ARROW", { 630, 10 }, 30, 1, birdTwo.color);
		}
		else
		{
			DrawTextEx(font, "SPACE: JUMP", { 562, 10 }, 30, 1, BLACK);
		}
	}

	void isPlayerAlive()
	{
		//CUANDO NO QUEDA NINGUN JUGADOR VIVO SE PASA A LA PANTALLA DE GAME OVER
		if (!bird.isAlive && !birdTwo.isAlive)
		{
			currentScreen = Screen::GameOver;
		}
	}
}