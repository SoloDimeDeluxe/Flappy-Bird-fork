#include "PowerUp.h"

#include <cstdlib>

#include "Collision.h"
#include "Player.h"

namespace rd
{
	static const int MAX_POWER_UPS = 3; //COMO MUCHO UNO POR CANIO
	static const int SPAWN_CHANCE = 30; //PORCENTAJE DE CANIOS QUE TRAEN UN POWER-UP
	static const float POWER_UP_SIZE = 30.0f;

	//DATOS DE CADA POWER-UP, EN EL MISMO ORDEN QUE EL ENUM
	static const PowerUpInfo POWER_UPS_INFO[static_cast<int>(PowerUpType::Count)] =
	{
		{ "", WHITE, 0.0f } //None
	};

	static PowerUp powerUps[MAX_POWER_UPS];

	void PowerUpInit()
	{
		for (int i = 0; i < MAX_POWER_UPS; i++)
		{
			powerUps[i].isActive = false;
		}
	}

	void PowerUpTrySpawn(Vector2 position)
	{
		//SOLO HAY POWER-UPS EN 2 JUGADORES
		int typesAmount = static_cast<int>(PowerUpType::Count) - 1; //SIN CONTAR NONE

		if (!isTwoPlayers || typesAmount <= 0 || rand() % 100 >= SPAWN_CHANCE)
		{
			return;
		}

		for (int i = 0; i < MAX_POWER_UPS; i++)
		{
			if (!powerUps[i].isActive)
			{
				//LA POSICION QUE LLEGA ES EL CENTRO DEL HUECO
				powerUps[i].position = { position.x - POWER_UP_SIZE / 2, position.y - POWER_UP_SIZE / 2 };
				powerUps[i].type = static_cast<PowerUpType>(rand() % typesAmount + 1);
				powerUps[i].isActive = true;
				return;
			}
		}
	}

	void PowerUpUpdate(float delta, float speed)
	{
		//SE MUEVEN A LA MISMA VELOCIDAD QUE LOS CANIOS
		for (int i = 0; i < MAX_POWER_UPS; i++)
		{
			if (powerUps[i].isActive)
			{
				powerUps[i].position.x -= speed * delta;

				if (powerUps[i].position.x + POWER_UP_SIZE < 0)
				{
					powerUps[i].isActive = false;
				}
			}
		}
	}

	void PowerUpDraw()
	{
		for (int i = 0; i < MAX_POWER_UPS; i++)
		{
			if (powerUps[i].isActive)
			{
				Vector2 center = { powerUps[i].position.x + POWER_UP_SIZE / 2, powerUps[i].position.y + POWER_UP_SIZE / 2 };

				DrawCircleV(center, POWER_UP_SIZE / 2, GetPowerUpInfo(powerUps[i].type).color);
				DrawCircleLinesV(center, POWER_UP_SIZE / 2, BLACK);
			}
		}
	}

	PowerUpType PowerUpCheckPickup(Vector2 position, Vector2 size)
	{
		for (int i = 0; i < MAX_POWER_UPS; i++)
		{
			if (powerUps[i].isActive && CheckRectangleCollision(position, size,
				powerUps[i].position, { POWER_UP_SIZE, POWER_UP_SIZE }))
			{
				powerUps[i].isActive = false;
				return powerUps[i].type;
			}
		}

		return PowerUpType::None;
	}

	PowerUpInfo GetPowerUpInfo(PowerUpType type)
	{
		return POWER_UPS_INFO[static_cast<int>(type)];
	}
}
