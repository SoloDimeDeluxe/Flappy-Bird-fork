#pragma once

#include "raylib.h"

#include "PowerUp.h"

namespace rd
{
	struct Player
	{
		Vector2 position = { 0,0 };
		Vector2 size = { 0,0 };
		int score = 0;
		float velocity = 0.0f;
		float jumpForce = 0.0f;
		bool isAlive = true;
		int jumpKey = KEY_NULL;
		Color color = ORANGE;
		float aliveTime = 0.0f; //PARA DESEMPATAR EN 2 JUGADORES
		float closestGapDistance = -1.0f; //LO MAS CERCA QUE PASO DEL BORDE EN EL CANIO ACTUAL
		int lastBonus = 0;
		bool isLastBonusPerfect = false;
		float bonusTimer = 0.0f;
		int lives = 1;
		float invulnerableTimer = 0.0f; //DESPUES DE PERDER UNA VIDA NO PUEDE CHOCAR POR UN RATO
		float startPositionY = 0.0f; //DONDE REAPARECE AL PERDER UNA VIDA
		PowerUpType activePowerUp = PowerUpType::None;
		float powerUpTimer = 0.0f;
	};

	enum class Winner
	{
		None = 0,
		PlayerOne,
		PlayerTwo
	};

	extern Player bird;
	extern Player birdTwo;
	extern bool isTwoPlayers;
	extern int bestScore;

	void PlayerInit();
	void PlayerUpdate(float delta);
	void PlayerDraw(Font font);
	void PlayerControlsDraw(Font font);
	void PlayerScoreDraw(Font font);
	Winner GetWinner();
	bool PlayerHasPowerUp(const Player& player, PowerUpType type);
}
