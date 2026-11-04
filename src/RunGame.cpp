#include "RunGame.h"
#include <ctime>
#include <cstdlib>
#include "raylib.h"
#include "ScreenManager.h"
#include "Player.h"
#include "Obstacle.h"

namespace rd
{
	void RunGame()
	{
		bool gameIsRunning = true;

		srand(static_cast<int>(time(nullptr)));
		float deltaTime = 0;

		InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Flappy Bird");
		
		//FONTS
		Font font = LoadFont("res/font/Muroslant.otf");

		//IMAGES
		Texture2D foreground = LoadTexture("res/Background/Parallax/farm_forward.png");
		Texture2D middleGround = LoadTexture("res/Background/Parallax/mountain_middle.png");
		Texture2D background = LoadTexture("res/Background/Parallax/sky_back.png");

		PlayerInit();
		ObstacleInit();

		while (!WindowShouldClose() && gameIsRunning)
		{
			ClearBackground(WHITE);
			deltaTime = GetFrameTime();

			Update(deltaTime, gameIsRunning);
			Draw(font);
		}

		UnloadFont(font);

		CloseWindow();
	}
}