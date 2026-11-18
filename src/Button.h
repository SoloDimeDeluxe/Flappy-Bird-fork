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

	const float MENU_BUTTON_POSITION_X = 530.0f;
	const float MENU_BUTTON_SEPARATION = 95.0f;

	void ButtonInit();
	void ButtonSetup(Button& button, float positionY, float textOffsetX);
	bool CheckCollisionMouseButton(Vector2 mousePosition, float buttonX,
		float buttonY, float buttonHeight, float buttonWidth);

	void IsMousePressed();
	void IsMousePressingBackButton();

	void BackButtonDraw();
	void ButtonDraw();
	void ButtonTextDraw(Font font);
}
