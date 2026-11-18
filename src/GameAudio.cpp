#include "GameAudio.h"

#include "ScreenManager.h"

namespace rd
{
	static const float MUSIC_VOLUME = 0.5f;
	static const float BONUS_PITCH = 1.5f;
	static const float POWER_UP_PITCH = 0.7f;

	GameAudio gameAudio;

	static Music* currentMusic = nullptr;
	static bool isMusicPaused = false;

	void GameAudioLoad()
	{
		//MUSICAS
		gameAudio.menuMusic = LoadMusicStream("res/audio/menu_music.ogg");
		gameAudio.gameMusic = LoadMusicStream("res/audio/game_music.ogg");
		SetMusicVolume(gameAudio.menuMusic, MUSIC_VOLUME);
		SetMusicVolume(gameAudio.gameMusic, MUSIC_VOLUME);

		//SONIDOS
		gameAudio.jump = LoadSound("res/audio/jump.wav");
		gameAudio.point = LoadSound("res/audio/point.wav");
		gameAudio.hit = LoadSound("res/audio/hit.wav");
		gameAudio.fall = LoadSound("res/audio/fall.wav");
		gameAudio.gameOver = LoadSound("res/audio/game_over.wav");
		gameAudio.click = LoadSound("res/audio/click.wav");
		gameAudio.countdown = LoadSound("res/audio/countdown.wav");

		//EL BONUS ES EL SONIDO DEL PUNTO PERO MAS AGUDO
		gameAudio.bonus = LoadSoundAlias(gameAudio.point);
		SetSoundPitch(gameAudio.bonus, BONUS_PITCH);

		//AGARRAR UN POWER-UP SUENA COMO EL PUNTO PERO MAS GRAVE
		gameAudio.powerUp = LoadSoundAlias(gameAudio.point);
		SetSoundPitch(gameAudio.powerUp, POWER_UP_PITCH);
	}

	void GameAudioUpdate()
	{
		//MENU, REGLAS Y CREDITOS TIENEN SU MUSICA, EL RESTO USA LA DEL GAMEPLAY
		Music* targetMusic = &gameAudio.gameMusic;

		if (currentScreen == Screen::Menu || currentScreen == Screen::Rules || currentScreen == Screen::Credits)
		{
			targetMusic = &gameAudio.menuMusic;
		}

		//CAMBIO DE MUSICA
		if (targetMusic != currentMusic)
		{
			if (currentMusic != nullptr)
			{
				StopMusicStream(*currentMusic);
			}

			currentMusic = targetMusic;
			PlayMusicStream(*currentMusic);
			isMusicPaused = false;
		}

		//EN PAUSA LA MUSICA TAMBIEN SE PAUSA
		if (currentScreen == Screen::Pause && !isMusicPaused)
		{
			PauseMusicStream(*currentMusic);
			isMusicPaused = true;
		}
		else if (currentScreen != Screen::Pause && isMusicPaused)
		{
			ResumeMusicStream(*currentMusic);
			isMusicPaused = false;
		}

		UpdateMusicStream(*currentMusic);
	}

	void GameAudioUnload()
	{
		UnloadMusicStream(gameAudio.menuMusic);
		UnloadMusicStream(gameAudio.gameMusic);

		UnloadSoundAlias(gameAudio.bonus);
		UnloadSoundAlias(gameAudio.powerUp);
		UnloadSound(gameAudio.jump);
		UnloadSound(gameAudio.point);
		UnloadSound(gameAudio.hit);
		UnloadSound(gameAudio.fall);
		UnloadSound(gameAudio.gameOver);
		UnloadSound(gameAudio.click);
		UnloadSound(gameAudio.countdown);

		currentMusic = nullptr;
	}
}
