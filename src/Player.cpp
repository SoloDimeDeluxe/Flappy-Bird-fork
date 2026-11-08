#include "Player.h"
#include "raylib.h"
#include "RunGame.h"
#include "Obstacle.h"
#include "Collision.h"

namespace rd
{
	Player bird;

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

		bird.textPosition.x = 1200;
		bird.textPosition.y = 670; //DENTRO DE LA VENTANA (ALTO 720)
		bird.fontSize = 40;
		bird.spacing = 1;
	}

	void PlayerUpdate(float delta)
	{
		if (IsKeyPressed(KEY_SPACE))
		{
			bird.velocity = bird.jumpForce;
		}

		//VELOCITY:
		bird.velocity += GRAVITY * delta;
		bird.position.y += delta * bird.velocity;

		if (bird.position.y + bird.radius > WINDOW_HEIGHT)
		{
			bird.isAlive = false;
			bird.position.y = WINDOW_HEIGHT - bird.radius;
		}
		else if (bird.position.y - bird.radius < 0)
		{
			bird.velocity = 0;
			bird.position.y = 0 + bird.radius;
		}

		isPlayerAlive();
	}

	void PlayerDraw()
	{
		DrawRectangleV(bird.position, bird.size, ORANGE); // x, y, width, height, color
	}

	void isPlayerAlive()
	{
		if (CheckRectangleCollision(bird.position, bird.size, pipeOne.position, pipeOne.size) ||
			CheckRectangleCollision(bird.position, bird.size, pipeTwo.position, pipeTwo.size) ||
			!bird.isAlive)
		{
			PlayerInit();
			ObstacleInit();
		}
	}
}