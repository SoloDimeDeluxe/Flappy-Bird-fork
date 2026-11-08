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
		sky.offset = 0.0f;

		mountain.position.x = 0;
		mountain.position.y = 310;
		mountain.offset = 0.0f;

		farm.position.x = 0;
		farm.position.y = 290;
		farm.offset = 0.0f;
	}

	void ParallaxUpdate(float delta)
	{
		sky.offset -= 10 * delta;
		mountain.offset -= 25 * delta;
		farm.offset -= 50 * delta;

		//EL LOOP SE REINICIA CADA 2 IMAGENES (UNA NORMAL Y UNA ESPEJADA)
		if (sky.offset <= -sky.texture.width * 2)
		{
			sky.offset += sky.texture.width * 2;
		}

		if (mountain.offset <= -mountain.texture.width * 2)
		{
			mountain.offset += mountain.texture.width * 2;
		}

		if (farm.offset <= -farm.texture.width * 2)
		{
			farm.offset += farm.texture.width * 2;
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
		bool isMirrored = false;

		//SE INTERCALA UNA COPIA NORMAL Y UNA ESPEJADA PARA QUE LOS BORDES CALCEN
		while (auxX < WINDOW_WIDTH)
		{
			if (isMirrored)
			{
				//ANCHO NEGATIVO EN EL RECORTE = IMAGEN DADA VUELTA HORIZONTALMENTE
				DrawTextureRec(texture, { 0, 0, -static_cast<float>(texture.width),
					static_cast<float>(texture.height) }, { auxX, position.y }, WHITE);
			}
			else
			{
				DrawTextureEx(texture, { auxX, position.y }, 0, 1, WHITE);
			}

			isMirrored = !isMirrored;
			auxX += texture.width;
		}
	}
}