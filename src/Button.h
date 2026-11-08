#pragma once
#include "raylib.h"

namespace rd
{
	struct Button
	{
		Vector2 position;
		Vector2 size;
		Vector2 textPosition;
		float textSize;
		float fontSize;
		float spacing;
	};

	extern Button play;
	extern Button playTwo;
	extern Button credits;
	extern Button exit;
	extern Button back;

	void ButtonInit();
	bool CheckCollisionMouseButton(Vector2 mousePosition, float buttonX,
		float buttonY, float buttonHeight, float buttonWidth);

	void IsMousePressed();
	void IsMousePressingBackButton();

	void BackButtonDraw();
	void ButtonDraw();
	void ButtonTextDraw(Font font);
}