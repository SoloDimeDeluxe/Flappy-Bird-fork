#include "Parallax.h"

#include "RunGame.h"

namespace rd
{
	//LAS CAPAS MAS LEJANAS VAN MAS LENTO
	static const float SKY_SPEED = 10.0f;
	static const float MOUNTAIN_SPEED = 25.0f;
	static const float FARM_SPEED = 50.0f;
	static const float MOUNTAIN_POSITION_Y = 310.0f;
	static const float FARM_POSITION_Y = 290.0f;

	Parallax sky;
	Parallax mountain;
	Parallax farm;

	static void ParallaxDrawMovement(Texture2D texture, Vector2 position, float offset);

	void ParallaxInit()
	{
		sky.position.x = 0;
		sky.position.y = 0;
		sky.offset = 0.0f;

		mountain.position.x = 0;
		mountain.position.y = MOUNTAIN_POSITION_Y;
		mountain.offset = 0.0f;

		farm.position.x = 0;
		farm.position.y = FARM_POSITION_Y;
		farm.offset = 0.0f;
	}

	void ParallaxUpdate(float delta)
	{
		sky.offset -= SKY_SPEED * delta;
		mountain.offset -= MOUNTAIN_SPEED * delta;
		farm.offset -= FARM_SPEED * delta;

		//EL LOOP SE REINICIA CADA 2 IMAGENES (UNA NORMAL Y UNA ESPEJADA)
		if (sky.offset <= -static_cast<float>(sky.texture.width * 2))
		{
			sky.offset += static_cast<float>(sky.texture.width * 2);
		}

		if (mountain.offset <= -static_cast<float>(mountain.texture.width * 2))
		{
			mountain.offset += static_cast<float>(mountain.texture.width * 2);
		}

		if (farm.offset <= -static_cast<float>(farm.texture.width * 2))
		{
			farm.offset += static_cast<float>(farm.texture.width * 2);
		}
	}

	void ParallaxDraw(Texture2D foreground, Texture2D middleGround,
		Texture2D background)
	{
		ParallaxDrawMovement(background, sky.position, sky.offset);
		ParallaxDrawMovement(middleGround, mountain.position, mountain.offset);
		ParallaxDrawMovement(foreground, farm.position, farm.offset);
	}

	static void ParallaxDrawMovement(Texture2D texture, Vector2 position, float offset)
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
			auxX += static_cast<float>(texture.width);
		}
	}
}