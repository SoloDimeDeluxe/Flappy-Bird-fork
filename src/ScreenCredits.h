#pragma once
#include "raylib.h"

namespace rd
{
	struct Credits
	{
		Vector2 textPosition;
		float fontSize;
		float spacing;
	};

	extern Credits name;
	extern Credits nameTwo;
	extern Credits tittleGameDev;

	void CreditsInit();
	void CreditsDraw(Font font);
}