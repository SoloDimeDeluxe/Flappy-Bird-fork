#include "Obstacle.h"

#include <cstdlib>

#include "RunGame.h"

namespace rd
{
	static const int MIN_PIPE_HEIGHT = 200;
	static const int MAX_PIPE_HEIGHT = 700;
	static const float PIPE_GAP = 200.0f; //HUECO ENTRE LOS DOS CANIOS
	static const float PIPE_WIDTH = 80.0f;

	Obstacle pipeOne;
	Obstacle pipeTwo;

	static float GetRandomPipeHeight();
	static void PipeRespawn();

	void ObstacleInit()
	{
		pipeOne.size.x = PIPE_WIDTH;
		pipeTwo.size.x = PIPE_WIDTH;

		//ALTURA AL AZAR DESDE EL ARRANQUE PARA QUE EL PRIMERO SE VEA
		PipeRespawn();
	}

	void ObstacleUpdate(float delta)
	{
		pipeOne.position.x -= delta * MAX_OBSTACLE_SPEED;
		pipeTwo.position.x -= delta * MAX_OBSTACLE_SPEED;

		//CUANDO SALE POR LA IZQUIERDA VUELVE POR LA DERECHA A OTRA ALTURA
		if (pipeOne.position.x + pipeOne.size.x < 0)
		{
			PipeRespawn();
		}
	}

	void ObstacleDraw()
	{
		DrawRectangleV(pipeOne.position, pipeOne.size, RED);
		DrawRectangleV(pipeTwo.position, pipeTwo.size, RED);
	}

	static float GetRandomPipeHeight()
	{
		return static_cast<float>(rand() % (MAX_PIPE_HEIGHT - MIN_PIPE_HEIGHT + 1) + MIN_PIPE_HEIGHT);
	}

	static void PipeRespawn()
	{
		//CANIO DE ABAJO
		pipeOne.position.x = WINDOW_WIDTH;
		pipeOne.position.y = GetRandomPipeHeight();
		pipeOne.size.y = WINDOW_HEIGHT - pipeOne.position.y;
		pipeOne.isPassed = false;

		//CANIO DE ARRIBA
		pipeTwo.position.x = WINDOW_WIDTH;
		pipeTwo.position.y = 0.0f;
		pipeTwo.size.y = pipeOne.position.y - PIPE_GAP;
	}
}
