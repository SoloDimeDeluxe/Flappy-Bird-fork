#include "Collision.h"

namespace rd
{
	bool CheckRectangleCollision(Vector2 rectangleOnePosition, Vector2 rectangleOneSize,
		Vector2 rectangleTwoPosition, Vector2 rectangleTwoSize)
	{
		//AABB: SI NINGUN LADO QUEDA AFUERA DEL OTRO RECTANGULO, SE ESTAN TOCANDO
		return !(rectangleOnePosition.x + rectangleOneSize.x < rectangleTwoPosition.x ||
			rectangleOnePosition.x > rectangleTwoPosition.x + rectangleTwoSize.x ||
			rectangleOnePosition.y + rectangleOneSize.y < rectangleTwoPosition.y ||
			rectangleOnePosition.y > rectangleTwoPosition.y + rectangleTwoSize.y);
	}
}
