#include "Obstacle.h"

#include <cstdlib>

#include "RunGame.h"
#include "Collision.h"
#include "ScreenManager.h"

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
	static float GetRandomFloat(float min, float max);
	static float GetReachableGapY(float min, float max);
	static int GetPipeSegments(const Obstacle& pipe, Rectangle segments[]);

	void ObstacleInit()
	{
		obstacleSpeed = NORMAL_SPEED;
		isHardMode = false;
		warningTimer = 0.0f;
		lastGapY = (WINDOW_HEIGHT - NORMAL_GAP_SIZE) / 2;

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
		Rectangle segments[MAX_SEGMENTS];

		for (int i = 0; i < MAX_OBSTACLES; i++)
		{
			int segmentsAmount = GetPipeSegments(pipes[i], segments);

			for (int j = 0; j < segmentsAmount; j++)
			{
				if (CheckRectangleCollision(position, size, { segments[j].x, segments[j].y },
					{ segments[j].width, segments[j].height }))
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
	}

	static float GetRandomFloat(float min, float max)
	{
		return min + static_cast<float>(rand() % (static_cast<int>(max - min) + 1));
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
