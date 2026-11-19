#pragma once

#include "raylib.h"

namespace rd
{
	struct Button
	{
		Vector2 position;
		Vector2 size;
		float fontSize;
		float spacing;
	};

	const float MENU_BUTTON_POSITION_X = 530.0f;
	const float MENU_BUTTON_SEPARATION = 95.0f;

	void ButtonInit();
	void ButtonSetup(Button& button, float positionY);
	bool IsMouseOverButton(const Button& button);

	void IsMousePressed();
	void IsMousePressingBackButton();

	void BackButtonDraw();
	void ButtonDraw();
	void ButtonTextDraw(Font font);
	void ButtonLabelDraw(Font font, const Button& button, const char* text);
}
