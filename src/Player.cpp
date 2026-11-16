#include "Player.h"

#include "RunGame.h"
#include "Obstacle.h"
#include "Collision.h"
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

	Player bird;
	Player birdTwo;
	bool isTwoPlayers = false;
	int bestScore = 0; //DE LA SESION

	static void CheckPipePassed();
	static void CheckPlayersAlive();
	static void PlayerMovement(Player& player, float delta);
	static void PlayerLabelDraw(Font font, const Player& player, const char* label);

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
		bird.velocity = PLAYER_START_VELOCITY;
		bird.jumpForce = PLAYER_JUMP_FORCE;
		bird.isAlive = true;
		bird.jumpKey = KEY_SPACE;
		bird.color = ORANGE;

		//JUGADOR 2: ARRANCA IGUAL QUE EL 1 PERO MAS ARRIBA, CON OTRA TECLA Y OTRO COLOR
		birdTwo = bird;
		birdTwo.position.y = PLAYER_TWO_START_POSITION_Y;
		birdTwo.jumpKey = KEY_UP;
		birdTwo.color = PURPLE;
		birdTwo.isAlive = isTwoPlayers; //EN MODO 1 JUGADOR NO PARTICIPA
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

		CheckPipePassed();
		CheckPlayersAlive();
	}

	void PlayerDraw(Font font)
	{
		//EN GAME OVER SE DIBUJAN TAMBIEN LOS MUERTOS PARA VER DONDE CHOCARON
		bool isGameOver = currentScreen == Screen::GameOver;

		if (bird.isAlive || isGameOver)
		{
			DrawRectangleV(bird.position, bird.size, bird.color); // x, y, width, height, color
		}

		if (isTwoPlayers)
		{
			//ETIQUETAS ARRIBA DE CADA JUGADOR PARA SABER QUIEN ES QUIEN
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
	}

	void PlayerControlsDraw(Font font)
	{
		//CONTROLES EN PANTALLA ARRIBA AL CENTRO
		if (isTwoPlayers)
		{
			//LOS DOS JUNTOS CENTRADOS, CADA UNO CON EL COLOR DE SU JUGADOR
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
		//GANA EL DE MAS PUNTOS, SI EMPATAN EL QUE DURO MAS
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
		//PUNTO PARA CADA JUGADOR VIVO CUANDO EL CANIO YA LO PASO
		if (!pipeOne.isPassed && pipeOne.position.x + pipeOne.size.x < bird.position.x)
		{
			pipeOne.isPassed = true;

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
		}
	}

	static void CheckPlayersAlive()
	{
		//CUANDO NO QUEDA NINGUN JUGADOR VIVO SE PASA A LA PANTALLA DE GAME OVER
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

		//VELOCITY:
		player.velocity += GRAVITY * delta;
		player.position.y += delta * player.velocity;

		//PISO Y TECHO SEGUN EL TAMANIO DEL RECTANGULO
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

		//SI YA SE CAYO NO SE CHEQUEA EL CHOQUE
		if (player.isAlive &&
			(CheckRectangleCollision(player.position, player.size, pipeOne.position, pipeOne.size) ||
			CheckRectangleCollision(player.position, player.size, pipeTwo.position, pipeTwo.size)))
		{
			player.isAlive = false;
			PlaySound(gameAudio.hit);
		}
	}

	static void PlayerLabelDraw(Font font, const Player& player, const char* label)
	{
		Vector2 labelSize = MeasureTextEx(font, label, LABEL_FONT_SIZE, TEXT_SPACING);
		Vector2 labelPosition = { player.position.x + (player.size.x - labelSize.x) / 2, player.position.y - LABEL_OFFSET_Y };

		DrawTextEx(font, label, labelPosition, LABEL_FONT_SIZE, TEXT_SPACING, player.color);
	}
}