#pragma once

#include "raylib.h"

namespace rd
{
	bool CheckRectangleCollision(Vector2 rectangleOnePosition, Vector2 rectangleOneSize,
		Vector2 rectangleTwoPosition, Vector2 rectangleTwoSize);
}
