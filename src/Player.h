#pragma once

#include "raylib.h"

namespace rd
{
	struct Player
	{
		Vector2 position = { 0,0 };
		Vector2 direction = { 0,0 };
		Vector2 size = { 0,0 };
		int score = 0;
		float rotation = 0.0f;
		float radius = 0.0f;
		float velocity = 0.0f;
		float jumpForce = 0.0f;
		bool isAlive = true;
		int jumpKey = KEY_NULL;
		Color color = ORANGE;
		float aliveTime = 0.0f; //PARA DESEMPATAR EN 2 JUGADORES
		float closestGapDistance = -1.0f; //LO MAS CERCA QUE PASO DEL BORDE EN EL CANIO ACTUAL
		int lastBonus = 0;
		float bonusTimer = 0.0f;
	};

	enum class Winner
	{
		None = 0,
		PlayerOne,
		PlayerTwo
	};

	const int GRAVITY = 500;

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
}
