#include "RunGame.h"

#include <ctime>
#include <cstdlib>

#include "ScreenManager.h"
#include "Player.h"
#include "Obstacle.h"
#include "Parallax.h"
#include "GameAudio.h"
#include "Button.h"

namespace rd
{
	void RunGame()
	{
		bool gameIsRunning = true;

		srand(static_cast<int>(time(nullptr)));
		float deltaTime = 0;

		InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
		SetExitKey(KEY_NULL); //ESC PAUSA, NO CIERRA EL JUEGO
		InitAudioDevice();

		//AUDIO
		GameAudioLoad();

		//FONTS
		Font font = LoadFont("res/font/Muroslant.otf");

		//IMAGES
		Texture2D foreground = LoadTexture("res/Background/Parallax/farm_forward.png");
		Texture2D middleGround = LoadTexture("res/Background/Parallax/mountain_middle.png");
		Texture2D background = LoadTexture("res/Background/Parallax/sky_back.png");

		//SE GUARDAN LAS TEXTURAS EN CADA CAPA PARA QUE EL LOOP USE SU ANCHO
		sky.texture = background;
		mountain.texture = middleGround;
		farm.texture = foreground;

		PlayerInit();
		ObstacleInit();
		ButtonInit(); //LAS POSICIONES DE LOS BOTONES NO CAMBIAN, ALCANZA CON PREPARARLOS UNA VEZ

		while (!WindowShouldClose() && gameIsRunning)
		{
			ClearBackground(WHITE);
			deltaTime = GetFrameTime();

			GameAudioUpdate();
			Update(deltaTime, gameIsRunning);
			Draw(font, foreground, middleGround, background);
		}

		UnloadFont(font);
		UnloadTexture(foreground);
		UnloadTexture(middleGround);
		UnloadTexture(background);
		GameAudioUnload();

		CloseAudioDevice();
		CloseWindow();
	}
}