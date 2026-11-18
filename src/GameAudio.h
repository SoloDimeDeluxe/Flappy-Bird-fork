#pragma once

#include "raylib.h"

namespace rd
{
	struct GameAudio
	{
		Music menuMusic;
		Music gameMusic;
		Sound jump;
		Sound point;
		Sound hit;
		Sound fall;
		Sound gameOver;
		Sound click;
		Sound countdown;
		Sound bonus;
		Sound powerUp;
	};

	extern GameAudio gameAudio;

	void GameAudioLoad();
	void GameAudioUpdate();
	void GameAudioUnload();
}
