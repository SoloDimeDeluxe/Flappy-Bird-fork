#pragma once

#include "raylib.h"

namespace rd
{
	struct Obstacle
	{
		float positionX;
		float width;
		float gapOneY;
		float gapTwoY;
		float gapSize;
		bool hasTwoGaps = false;
		bool isPassed = false;
	};

	void ObstacleInit();
	void ObstacleUpdate(float delta, int highestScore);
	void ObstacleDraw();
	void DifficultyWarningDraw(Font font);
	bool ObstacleCheckCollision(Vector2 position, Vector2 size);
	bool ObstacleCheckPassed(float positionX);
	float ObstacleGetGapDistance(Vector2 position, Vector2 size);
}
