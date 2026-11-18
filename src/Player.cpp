#include "Player.h"

#include "RunGame.h"
#include "Obstacle.h"
#include "ScreenManager.h"
#include "ScreenGameOver.h"
#include "GameAudio.h"

namespace rd
{
	static const float PLAYER_START_POSITION_X = 200.0f;
	static const float PLAYER_ONE_START_POSITION_Y = 400.0f;
	static const float PLAYER_TWO_START_POSITION_Y = 250.0f;
	static const float PLAYER_SIZE = 50.0f;
	static const float PLAYER_START_VELOCITY = 300.0f;
	static const float PLAYER_JUMP_FORCE = -200.0f;

	static const float LABEL_FONT_SIZE = 30.0f;
	static const float LABEL_OFFSET_Y = 30.0f;
	static const float CONTROLS_FONT_SIZE = 30.0f;
	static const float CONTROLS_POSITION_Y = 10.0f;
	static const float CONTROLS_SEPARATION = 40.0f;
	static const float SCORE_FONT_SIZE = 40.0f;
	static const float SCORE_MARGIN = 20.0f;
	static const float TEXT_SPACING = 1.0f;

	//BONUS POR PASAR PEGADO AL BORDE DEL HUECO
	static const float PERFECT_DISTANCE = 8.0f;
	static const float CLOSE_DISTANCE = 20.0f;
	static const int PERFECT_BONUS = 2;
	static const int CLOSE_BONUS = 1;
	static const float BONUS_TEXT_DURATION = 0.8f;
	static const float BONUS_TEXT_RISE = 40.0f; //CUANTO SUBE EL TEXTO MIENTRAS SE DESVANECE
	static const float BONUS_FONT_SIZE = 30.0f;
	static const float BONUS_OFFSET_Y = 65.0f;

	Player bird;
	Player birdTwo;
	bool isTwoPlayers = false;
	int bestScore = 0;

	static void CheckPipePassed();
	static void CheckPlayersAlive();
	static void PlayerMovement(Player& player, float delta);
	static void PlayerLabelDraw(Font font, const Player& player, const char* label);
	static void CheckCloseBonus(Player& player);
	static void BonusTextDraw(Font font, const Player& player);

	void PlayerInit()
	{
		bird.position.x = PLAYER_START_POSITION_X;
		bird.position.y = PLAYER_ONE_START_POSITION_Y;
		bird.direction.x = 0;
		bird.direction.y = 0;
		bird.size.x = PLAYER_SIZE;
		bird.size.y = PLAYER_SIZE;
		bird.rotation = 0;
		bird.score = 0;
		bird.aliveTime = 0.0f;
		bird.closestGapDistance = -1.0f;
		bird.lastBonus = 0;
		bird.bonusTimer = 0.0f;
		bird.velocity = PLAYER_START_VELOCITY;
		bird.jumpForce = PLAYER_JUMP_FORCE;
		bird.isAlive = true;
		bird.jumpKey = KEY_SPACE;
		bird.color = ORANGE;

		birdTwo = bird;
		birdTwo.position.y = PLAYER_TWO_START_POSITION_Y;
		birdTwo.jumpKey = KEY_UP;
		birdTwo.color = PURPLE;
		birdTwo.isAlive = isTwoPlayers;
	}

	void PlayerUpdate(float delta)
	{
		if (bird.isAlive)
		{
			PlayerMovement(bird, delta);
		}
		if (birdTwo.isAlive)
		{
			PlayerMovement(birdTwo, delta);
		}

		if (bird.bonusTimer > 0.0f)
		{
			bird.bonusTimer -= delta;
		}
		if (birdTwo.bonusTimer > 0.0f)
		{
			birdTwo.bonusTimer -= delta;
		}

		CheckPipePassed();
		CheckPlayersAlive();
	}

	void PlayerDraw(Font font)
	{
		bool isGameOver = currentScreen == Screen::GameOver;

		if (bird.isAlive || isGameOver)
		{
			DrawRectangleV(bird.position, bird.size, bird.color);
		}

		if (isTwoPlayers)
		{
			if (bird.isAlive || isGameOver)
			{
				PlayerLabelDraw(font, bird, "P1");
			}
			if (birdTwo.isAlive || isGameOver)
			{
				DrawRectangleV(birdTwo.position, birdTwo.size, birdTwo.color);
				PlayerLabelDraw(font, birdTwo, "P2");
			}
		}

		BonusTextDraw(font, bird);
		BonusTextDraw(font, birdTwo);
	}

	void PlayerControlsDraw(Font font)
	{
		if (isTwoPlayers)
		{
			const char* controlsOneText = "P1: SPACE";
			const char* controlsTwoText = "P2: UP ARROW";
			Vector2 controlsOneSize = MeasureTextEx(font, controlsOneText, CONTROLS_FONT_SIZE, TEXT_SPACING);
			Vector2 controlsTwoSize = MeasureTextEx(font, controlsTwoText, CONTROLS_FONT_SIZE, TEXT_SPACING);
			float startX = (WINDOW_WIDTH - (controlsOneSize.x + CONTROLS_SEPARATION + controlsTwoSize.x)) / 2;

			DrawTextEx(font, controlsOneText, { startX, CONTROLS_POSITION_Y },
				CONTROLS_FONT_SIZE, TEXT_SPACING, bird.color);
			DrawTextEx(font, controlsTwoText, { startX + controlsOneSize.x + CONTROLS_SEPARATION, CONTROLS_POSITION_Y },
				CONTROLS_FONT_SIZE, TEXT_SPACING, birdTwo.color);
		}
		else
		{
			const char* controlsText = "SPACE: JUMP";
			Vector2 controlsSize = MeasureTextEx(font, controlsText, CONTROLS_FONT_SIZE, TEXT_SPACING);

			DrawTextEx(font, controlsText, { (WINDOW_WIDTH - controlsSize.x) / 2, CONTROLS_POSITION_Y },
				CONTROLS_FONT_SIZE, TEXT_SPACING, BLACK);
		}
	}

	void PlayerScoreDraw(Font font)
	{
		if (isTwoPlayers)
		{
			const char* scoreOneText = TextFormat("P1: %i", bird.score);
			const char* scoreTwoText = TextFormat("P2: %i", birdTwo.score);
			Vector2 scoreOneSize = MeasureTextEx(font, scoreOneText, SCORE_FONT_SIZE, TEXT_SPACING);
			Vector2 scoreTwoSize = MeasureTextEx(font, scoreTwoText, SCORE_FONT_SIZE, TEXT_SPACING);

			DrawTextEx(font, scoreOneText, { WINDOW_WIDTH - scoreOneSize.x - SCORE_MARGIN, SCORE_MARGIN },
				SCORE_FONT_SIZE, TEXT_SPACING, bird.color);
			DrawTextEx(font, scoreTwoText, { WINDOW_WIDTH - scoreTwoSize.x - SCORE_MARGIN, SCORE_MARGIN + scoreOneSize.y },
				SCORE_FONT_SIZE, TEXT_SPACING, birdTwo.color);
		}
		else
		{
			const char* scoreText = TextFormat("SCORE: %i", bird.score);
			Vector2 scoreSize = MeasureTextEx(font, scoreText, SCORE_FONT_SIZE, TEXT_SPACING);

			DrawTextEx(font, scoreText, { WINDOW_WIDTH - scoreSize.x - SCORE_MARGIN, SCORE_MARGIN },
				SCORE_FONT_SIZE, TEXT_SPACING, BLACK);
		}
	}

	Winner GetWinner()
	{
		if (bird.score != birdTwo.score)
		{
			return bird.score > birdTwo.score ? Winner::PlayerOne : Winner::PlayerTwo;
		}
		if (bird.aliveTime != birdTwo.aliveTime)
		{
			return bird.aliveTime > birdTwo.aliveTime ? Winner::PlayerOne : Winner::PlayerTwo;
		}

		return Winner::None;
	}

	static void CheckPipePassed()
	{
		if (ObstacleCheckPassed(bird.position.x))
		{
			if (bird.isAlive || birdTwo.isAlive)
			{
				PlaySound(gameAudio.point);
			}

			if (bird.isAlive)
			{
				bird.score++;
			}
			if (birdTwo.isAlive)
			{
				birdTwo.score++;
			}

			CheckCloseBonus(bird);
			CheckCloseBonus(birdTwo);
		}
	}

	static void CheckPlayersAlive()
	{
		if (!bird.isAlive && !birdTwo.isAlive)
		{
			if (bird.score > bestScore)
			{
				bestScore = bird.score;
			}
			if (birdTwo.score > bestScore)
			{
				bestScore = birdTwo.score;
			}

			GameOverStart();
		}
	}

	static void PlayerMovement(Player& player, float delta)
	{
		player.aliveTime += delta;

		if (IsKeyPressed(player.jumpKey))
		{
			player.velocity = player.jumpForce;
			PlaySound(gameAudio.jump);
		}

		player.velocity += GRAVITY * delta;
		player.position.y += delta * player.velocity;

		if (player.position.y + player.size.y > WINDOW_HEIGHT)
		{
			player.isAlive = false;
			player.position.y = WINDOW_HEIGHT - player.size.y;
			PlaySound(gameAudio.fall);
		}
		else if (player.position.y < 0)
		{
			player.velocity = 0;
			player.position.y = 0;
		}

		if (player.isAlive && ObstacleCheckCollision(player.position, player.size))
		{
			player.isAlive = false;
			PlaySound(gameAudio.hit);
		}

		//MIENTRAS PASA EL CANIO SE GUARDA LO MAS CERCA QUE ESTUVO DEL BORDE
		float gapDistance = ObstacleGetGapDistance(player.position, player.size);

		if (gapDistance >= 0.0f && (player.closestGapDistance < 0.0f || gapDistance < player.closestGapDistance))
		{
			player.closestGapDistance = gapDistance;
		}
	}

	static void PlayerLabelDraw(Font font, const Player& player, const char* label)
	{
		Vector2 labelSize = MeasureTextEx(font, label, LABEL_FONT_SIZE, TEXT_SPACING);
		Vector2 labelPosition = { player.position.x + (player.size.x - labelSize.x) / 2, player.position.y - LABEL_OFFSET_Y };

		DrawTextEx(font, label, labelPosition, LABEL_FONT_SIZE, TEXT_SPACING, player.color);
	}

	static void CheckCloseBonus(Player& player)
	{
		int bonus = 0;

		if (player.isAlive && player.closestGapDistance >= 0.0f)
		{
			if (player.closestGapDistance < PERFECT_DISTANCE)
			{
				bonus = PERFECT_BONUS;
			}
			else if (player.closestGapDistance < CLOSE_DISTANCE)
			{
				bonus = CLOSE_BONUS;
			}
		}

		if (bonus > 0)
		{
			player.score += bonus;
			player.lastBonus = bonus;
			player.bonusTimer = BONUS_TEXT_DURATION;
			PlaySound(gameAudio.bonus);
		}

		//EL SIGUIENTE CANIO EMPIEZA DE CERO
		player.closestGapDistance = -1.0f;
	}

	static void BonusTextDraw(Font font, const Player& player)
	{
		if (player.bonusTimer <= 0.0f)
		{
			return;
		}

		//EL TEXTO SUBE Y SE VA DESVANECIENDO
		float progress = 1.0f - player.bonusTimer / BONUS_TEXT_DURATION;
		const char* bonusText = player.lastBonus == PERFECT_BONUS ? "+2 PERFECT!" : "+1 CLOSE!";
		Vector2 textSize = MeasureTextEx(font, bonusText, BONUS_FONT_SIZE, TEXT_SPACING);
		Vector2 textPosition = { player.position.x + (player.size.x - textSize.x) / 2,
			player.position.y - BONUS_OFFSET_Y - BONUS_TEXT_RISE * progress };

		DrawTextEx(font, bonusText, textPosition, BONUS_FONT_SIZE, TEXT_SPACING,
			Fade(player.color, player.bonusTimer / BONUS_TEXT_DURATION));
	}
}