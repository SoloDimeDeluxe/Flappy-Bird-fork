#include "Obstacle.h"

#include "RunGame.h"
#include "ScreenManager.h"
#include "PowerUp.h"

namespace rd
{
	static const int MAX_OBSTACLES = 3;
	static const int MAX_SEGMENTS = 3;	
	static const float PIPE_WIDTH = 80.0f;
	static const float PIPE_SEPARATION = 600.0f;
	static const float MAX_GAP_CHANGE = 220.0f;
	static const float SCREEN_MARGIN = 60.0f;

	static const float NORMAL_SPEED = 300.0f;
	static const float NORMAL_GAP_SIZE = 200.0f;

	static const int HARD_MODE_SCORE = 10;
	static const float HARD_SPEED = 380.0f;
	static const float HARD_GAP_SIZE = 160.0f;
	static const float MIN_WALL_BETWEEN_GAPS = 120.0f;
	static const float MAX_WALL_BETWEEN_GAPS = 220.0f;

	static const float WARNING_DURATION = 1.5f;
	static const float WARNING_FONT_SIZE = 80.0f;
	static const float WARNING_POSITION_Y = 120.0f;

	static Obstacle pipes[MAX_OBSTACLES];
	static float obstacleSpeed = NORMAL_SPEED;
	static bool isHardMode = false;
	static float warningTimer = 0.0f;
	static float lastGapY = 0.0f;

	static void PipeRespawn(Obstacle& pipe, float positionX);
	static float GetDistanceToGapEdge(float gapY, float gapSize, Vector2 position, Vector2 size);
	static float GetRandomFloat(float min, float max);
	static float GetReachableGapY(float min, float max);
	static int GetPipeSegments(const Obstacle& pipe, Rectangle segments[]);

	void ObstacleInit()
	{
		obstacleSpeed = NORMAL_SPEED;
		isHardMode = false;
		warningTimer = 0.0f;
		lastGapY = (WINDOW_HEIGHT - NORMAL_GAP_SIZE) / 2;

		PowerUpInit(); //ANTES DE ARMAR LOS CANIOS, QUE SON LOS QUE TRAEN LOS POWER-UPS

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			PipeRespawn(pipes[i], WINDOW_WIDTH + PIPE_SEPARATION * static_cast<float>(i));
		}
	}

	void ObstacleUpdate(float delta, int highestScore)
	{
		if (!isHardMode && highestScore >= HARD_MODE_SCORE)
		{
			isHardMode = true;
			obstacleSpeed = HARD_SPEED;
			warningTimer = WARNING_DURATION;
		}

		if (warningTimer > 0.0f)
		{
			warningTimer -= delta;
		}

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			pipes[i].positionX -= obstacleSpeed * delta;
		}

		PowerUpUpdate(delta, obstacleSpeed);

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			if (pipes[i].positionX + pipes[i].width < 0)
			{
				float lastPositionX = pipes[0].positionX;

				for (int j = 1; j < MAX_OBSTACLES; j++)
				{
					if (pipes[j].positionX > lastPositionX)
					{
						lastPositionX = pipes[j].positionX;
					}
				}

				PipeRespawn(pipes[i], lastPositionX + PIPE_SEPARATION);
			}
		}
	}

	void ObstacleDraw()
	{
		Rectangle segments[MAX_SEGMENTS];

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			int segmentsAmount = GetPipeSegments(pipes[i], segments);

			for (int j = 0; j < segmentsAmount; j++)
			{
				DrawRectangleRec(segments[j], RED);
			}
		}

		PowerUpDraw();
	}

	void DifficultyWarningDraw(Font font)
	{
		if (warningTimer > 0.0f)
		{
			DrawCenteredText(font, "SPEED UP!", WARNING_POSITION_Y, WARNING_FONT_SIZE, RED);
		}
	}

	bool ObstacleCheckCollision(Vector2 position, Vector2 size)
	{
		//SE ARMA EL RECTANGULO DEL JUGADOR PARA USAR LA COLISION QUE YA TRAE RAYLIB
		Rectangle playerRectangle = { position.x, position.y, size.x, size.y };
		Rectangle segments[MAX_SEGMENTS];

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			int segmentsAmount = GetPipeSegments(pipes[i], segments);

			for (int j = 0; j < segmentsAmount; j++)
			{
				if (CheckCollisionRecs(playerRectangle, segments[j]))
				{
					return true;
				}
			}
		}

		return false;
	}

	bool ObstacleCheckPassed(float positionX)
	{
		bool isAnyPassed = false;

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			if (!pipes[i].isPassed && pipes[i].positionX + pipes[i].width < positionX)
			{
				pipes[i].isPassed = true;
				isAnyPassed = true;
			}
		}

		return isAnyPassed;
	}

	float ObstacleGetGapDistance(Vector2 position, Vector2 size)
	{
		//DEVUELVE QUE TAN CERCA DEL BORDE DEL HUECO ESTA EL PAJARO, O -1 SI NO ESTA PASANDO NINGUN CANIO
		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			bool isInsidePipe = position.x + size.x > pipes[i].positionX &&
				position.x < pipes[i].positionX + pipes[i].width;

			if (isInsidePipe)
			{
				float distance = GetDistanceToGapEdge(pipes[i].gapOneY, pipes[i].gapSize, position, size);

				if (distance < 0.0f && pipes[i].hasTwoGaps)
				{
					distance = GetDistanceToGapEdge(pipes[i].gapTwoY, pipes[i].gapSize, position, size);
				}

				return distance;
			}
		}

		return -1.0f;
	}

	static void PipeRespawn(Obstacle& pipe, float positionX)
	{
		pipe.positionX = positionX;
		pipe.width = PIPE_WIDTH;
		pipe.isPassed = false;
		pipe.hasTwoGaps = isHardMode;

		if (pipe.hasTwoGaps)
		{
			pipe.gapSize = HARD_GAP_SIZE;
			float wallBetweenGaps = GetRandomFloat(MIN_WALL_BETWEEN_GAPS, MAX_WALL_BETWEEN_GAPS);
			float maxGapOneY = WINDOW_HEIGHT - SCREEN_MARGIN - pipe.gapSize * 2 - wallBetweenGaps;

			pipe.gapOneY = GetReachableGapY(SCREEN_MARGIN, maxGapOneY);
			pipe.gapTwoY = pipe.gapOneY + pipe.gapSize + wallBetweenGaps;
		}
		else
		{
			pipe.gapSize = NORMAL_GAP_SIZE;
			pipe.gapOneY = GetReachableGapY(SCREEN_MARGIN, WINDOW_HEIGHT - SCREEN_MARGIN - pipe.gapSize);
			pipe.gapTwoY = 0.0f;
		}

		lastGapY = pipe.gapOneY;

		//A VECES EL CANIO TRAE UN POWER-UP EN EL MEDIO DE UNO DE SUS HUECOS
		float powerUpGapY = pipe.gapOneY;

		if (pipe.hasTwoGaps && GetRandomValue(0, 1) == 0)
		{
			powerUpGapY = pipe.gapTwoY;
		}

		PowerUpTrySpawn({ pipe.positionX + pipe.width / 2, powerUpGapY + pipe.gapSize / 2 });
	}

	static float GetDistanceToGapEdge(float gapY, float gapSize, Vector2 position, Vector2 size)
	{
		float distanceToTop = position.y - gapY;
		float distanceToBottom = gapY + gapSize - (position.y + size.y);

		//SI NO ESTA ADENTRO DE ESTE HUECO NO CUENTA
		if (distanceToTop < 0.0f || distanceToBottom < 0.0f)
		{
			return -1.0f;
		}

		return distanceToTop < distanceToBottom ? distanceToTop : distanceToBottom;
	}

	static float GetRandomFloat(float min, float max)
	{
		//GETRANDOMVALUE DE RAYLIB DEVUELVE UN ENTERO ENTRE LOS DOS VALORES (INCLUIDOS)
		return min + static_cast<float>(GetRandomValue(0, static_cast<int>(max - min)));
	}

	static float GetReachableGapY(float min, float max)
	{
		if (min < lastGapY - MAX_GAP_CHANGE)
		{
			min = lastGapY - MAX_GAP_CHANGE;
		}
		if (max > lastGapY + MAX_GAP_CHANGE)
		{
			max = lastGapY + MAX_GAP_CHANGE;
		}
		if (min > max)
		{
			min = max;
		}

		return GetRandomFloat(min, max);
	}

	static int GetPipeSegments(const Obstacle& pipe, Rectangle segments[])
	{
		int segmentsAmount = 0;
		float gapOneEnd = pipe.gapOneY + pipe.gapSize;

		segments[segmentsAmount++] = { pipe.positionX, 0.0f, pipe.width, pipe.gapOneY };

		if (pipe.hasTwoGaps)
		{
			segments[segmentsAmount++] = { pipe.positionX, gapOneEnd, pipe.width, pipe.gapTwoY - gapOneEnd };
			segments[segmentsAmount++] = { pipe.positionX, pipe.gapTwoY + pipe.gapSize, pipe.width,
				WINDOW_HEIGHT - (pipe.gapTwoY + pipe.gapSize) };
		}
		else
		{
			segments[segmentsAmount++] = { pipe.positionX, gapOneEnd, pipe.width, WINDOW_HEIGHT - gapOneEnd };
		}

		return segmentsAmount;
	}
}
