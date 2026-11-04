#include "Parallax.h"
#include "raylib.h"

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
		mountain.position.y = 0;
		mountain.offset = 0.0f;

		farm.position.x = 0;
		farm.position.y = 0;
		farm.offset = 0.0f;
	}

	void ParallaxUpdate(float delta)
	{
		sky.offset -= 10 * delta;
		mountain.offset -= 10 * delta;
		farm.offset -= 10 * delta;
	}

	void ParallaxDraw(Texture2D foreground, Texture2D middleGround,
		Texture2D background)
	{
		ParallaxDrawMovement(foreground, sky.position, sky.offset);
		ParallaxDrawMovement(middleGround, mountain.position, mountain.offset);
		ParallaxDrawMovement(background, farm.position, farm.offset);
	}

	void ParallaxDrawMovement(Texture2D texture, Vector2 position, float offset)
	{
		float auxX = position.x + offset;

		while (auxX < 1280)
		{
			DrawTextureEx(texture, { auxX, position.y }, 0, 1, WHITE);

			auxX += texture.width;
		}
	}
}