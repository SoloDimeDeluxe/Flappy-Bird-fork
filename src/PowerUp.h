#pragma once

#include "raylib.h"

namespace rd
{
	//PARA AGREGAR UN POWER-UP NUEVO: SE AGREGA ACA (ANTES DE COUNT)
	//Y SE CARGAN SUS DATOS EN POWER_UPS_INFO (PowerUp.cpp), EN EL MISMO ORDEN
	enum class PowerUpType
	{
		None = 0,
		DoublePoints,
		Count
	};

	struct PowerUpInfo
	{
		const char* name;
		Color color;
		float duration; //SEGUNDOS QUE DURA EL EFECTO
	};

	struct PowerUp
	{
		Vector2 position;
		PowerUpType type = PowerUpType::None;
		bool isActive = false;
	};

	void PowerUpInit();
	void PowerUpTrySpawn(Vector2 position);
	void PowerUpUpdate(float delta, float speed);
	void PowerUpDraw();
	PowerUpType PowerUpCheckPickup(Vector2 position, Vector2 size);
	PowerUpInfo GetPowerUpInfo(PowerUpType type);
}
