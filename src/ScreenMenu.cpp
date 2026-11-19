#include "ScreenMenu.h"

#include "RunGame.h"
#include "Button.h"
#include "ScreenManager.h"

namespace rd
{
	static const float TITLE_FONT_SIZE = 110.0f;
	static const float TITLE_POSITION_Y = 50.0f;
	static const char* VERSION_TEXT = "v1.0";
	static const float VERSION_MARGIN = 15.0f; //DISTANCIA AL BORDE DE LA PANTALLA
	static const float VERSION_FONT_SIZE = 40.0f;
	static const float VERSION_SPACING = 1.0f;

	void MenuUpdate()
	{
		MenuButtonsUpdate();
	}

	void MenuDraw(Font font)
	{
		//LA VERSION VA EN LA ESQUINA DE ABAJO A LA DERECHA, CALCULADA SEGUN EL TAMANIO DE LA VENTANA
		Vector2 versionSize = MeasureTextEx(font, VERSION_TEXT, VERSION_FONT_SIZE, VERSION_SPACING);
		Vector2 versionPosition = { WINDOW_WIDTH - versionSize.x - VERSION_MARGIN, WINDOW_HEIGHT - versionSize.y - VERSION_MARGIN };

		DrawTextEx(font, VERSION_TEXT, versionPosition, VERSION_FONT_SIZE, VERSION_SPACING, BLACK);
		DrawCenteredText(font, "FLAPPY BIRD", TITLE_POSITION_Y, TITLE_FONT_SIZE, ORANGE);

		ButtonDraw();
		ButtonTextDraw(font);
	}
}
