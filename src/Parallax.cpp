#include "Parallax.h"
#include "raylib.h"
#include "RunGame.h"

namespace rd
{
	Parallax sky;
	Parallax mountain;
	Parallax farm;

	void ParallaxInit()
	{
		sky.position.x = 0;
		sky.position.y = 0;
		sky.texture.width = 0;
		sky.texture.height = 0;
		sky.offset = 0.0f;

		mountain.position.x = 0;
		mountain.position.y = 310;
		mountain.offset = 0.0f;
		mountain.texture.width = 0;
		mountain.texture.height = 0;
		mountain.offset = 0.0f;

		farm.position.x = 0;
		farm.position.y = 290;
		farm.offset = 0.0f;
		farm.texture.width = 0;
		farm.texture.height = 0;
		farm.offset = 0.0f;
	}

	void ParallaxUpdate(float delta)
	{
		sky.offset -= 10 * delta;
		mountain.offset -= 25 * delta;
		farm.offset -= 50 * delta;

		if (sky.offset <= -sky.texture.width)
		{
			sky.offset += sky.texture.width;
		}

		if (mountain.offset <= -mountain.texture.width)
		{
			mountain.offset += mountain.texture.width;
		}

		if (farm.offset <= -farm.texture.width)
		{
			farm.offset += farm.texture.width;
		}
	}

	void ParallaxDraw(Texture2D foreground, Texture2D middleGround,
		Texture2D background)
	{
		ParallaxDrawMovement(background, sky.position, sky.offset);
		ParallaxDrawMovement(middleGround, mountain.position, mountain.offset);
		ParallaxDrawMovement(foreground, farm.position, farm.offset);
	}

	void ParallaxDrawMovement(Texture2D texture, Vector2 position, float offset)
	{
		float auxX = position.x + offset;

		while (auxX < WINDOW_WIDTH)
		{
			DrawTextureEx(texture, { auxX, position.y }, 0, 1, WHITE);

			auxX += texture.width;
		}
	}
}