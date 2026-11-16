#include "ScreenExit.h"

#include "ScreenManager.h"

namespace rd
{
	void ExitUpdate(bool& gameIsRunning)
	{
		if (currentScreen == Screen::Exit)
		{
			gameIsRunning = false;
		}
	}
}