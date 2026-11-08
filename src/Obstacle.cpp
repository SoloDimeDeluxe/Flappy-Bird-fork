#include "Obstacle.h"
#include <ctime>
#include <cstdlib>
#include "raylib.h"
#include "RunGame.h"
#include "Player.h"

namespace rd
{
	Obstacle pipeOne;
	Obstacle pipeTwo;

	void ObstacleInit()
	{
		//SE LES DA ALTURA AL AZAR DESDE EL ARRANQUE PARA QUE LA PRIMERA PASADA SE VEA
		pipeOne.position.x = WINDOW_WIDTH;
		pipeOne.position.y = static_cast<float>(rand() % (700 - 200 + 1) + 200);
		pipeOne.size.x = 80;
		pipeOne.size.y = WINDOW_HEIGHT - pipeOne.position.y;

		pipeTwo.position.x = WINDOW_WIDTH;
		pipeTwo.position.y = 0;
		pipeTwo.size.x = 80;
		pipeTwo.size.y = (pipeOne.position.y - 200);
	}

	void ObstacleUpdate(float delta)
	{
		pipeOne.position.x -= delta * MAX_OBSTACLE_SPEED;
		pipeTwo.position.x -= delta * MAX_OBSTACLE_SPEED;

		if (pipeOne.position.x + pipeOne.size.x < 0)
		{
			pipeOne.position.y = static_cast<float>(rand() % (700 - 200 + 1) + 200);
			pipeOne.size.y = WINDOW_HEIGHT - pipeOne.position.y;
			pipeOne.position.x = WINDOW_WIDTH;
		}
		if (pipeTwo.position.x + pipeTwo.size.x < 0)
		{
			pipeTwo.position.y = 0.0f;
			pipeTwo.size.y = (pipeOne.position.y - 200);
			pipeTwo.position.x = WINDOW_WIDTH;
		}

	}

	void ObstacleDraw()
	{
		DrawRectangleV(pipeOne.position, pipeOne.size, RED);
		DrawRectangleV(pipeTwo.position, pipeTwo.size, RED);
	}
}