#pragma once
#include "raylib.h"

namespace rd
{
	struct Parallax
	{
		Vector2 position;
		Texture2D texture;
		float offset;
	};

	extern Parallax sky;
	extern Parallax mountain;
	extern Parallax farm;

	void ParallaxInit();
	void ParallaxUpdate(float delta);
	void ParallaxDraw(Texture2D foreground, Texture2D middleGround,
		Texture2D background);
	void ParallaxDrawMovement(Texture2D texture, Vector2 position,
		float offset);

}