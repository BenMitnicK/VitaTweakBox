#include "forecast.h"
#include "net.h"
#include "weather.h"
#include "../main.h"
#include "../config.h"
#include "../init.h"
#include "../theme.h"
#include "../language.h"
#include "../message_dialog.h"
#include "../ime_dialog.h"
#include "../utils.h"
#include "../file.h"
#include "../touch.h"

static int n_ForeCast_entries = 0;
ForeCastMenu ForeCast_menu;

void initForeCastMenu() {

	memset(&ForeCast_menu, 0, sizeof(ForeCastMenu));
	ForeCast_menu.status = FORECAST_MENU_CLOSED;
	n_ForeCast_entries = 1;
	
	initWeatherData();

}

void openForeCastMenu() {
	ForeCast_menu.status = FORECAST_MENU_OPENING;
}

void closeForeCastMenu() {
	ForeCast_menu.status = FORECAST_MENU_CLOSING;
}

int getForeCastMenuStatus() {
	return ForeCast_menu.status;
}

void fc_mainMenu()
{			
		if (checkFileExist("ux0:VitaTweakBox/tweaks/Forecast/weather.txt"))
			displayWeatherContent();
}

void drawForeCastMenu() {
  
	if (ForeCast_menu.status == FORECAST_MENU_CLOSED)
		return;

	// Closing settings menu
	if (ForeCast_menu.status == FORECAST_MENU_CLOSING) {
		if (ForeCast_menu.cur_pos > 0.0f) {
			ForeCast_menu.cur_pos -= easeOut(0.0f, ForeCast_menu.cur_pos, 0.25f, 0.01f);
		} else {
			ForeCast_menu.status = FORECAST_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (ForeCast_menu.status == FORECAST_MENU_OPENING) {
		if (ForeCast_menu.cur_pos < SCREEN_HEIGHT) {
			ForeCast_menu.cur_pos += easeOut(ForeCast_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			ForeCast_menu.status = FORECAST_MENU_OPENED;
		}
	}

	// Draw settings menu
	vita2d_draw_texture(background,  129, ForeCast_menu.cur_pos - 463);
	
	if (ForeCast_menu.cur_pos > 0.0f) {
		fc_mainMenu();
	}
}

static int agreement = FORECAST_AGREEMENT_NONE;

void ForeCastAgree() {
	agreement = FORECAST_AGREEMENT_AGREE;
}

void ForeCastDisagree() {
	agreement = FORECAST_AGREEMENT_DISAGREE;
}

void ForeCastMenuCtrl() {

	// Agreement
	if (agreement != FORECAST_AGREEMENT_NONE) {
		agreement = FORECAST_AGREEMENT_NONE;
	}

	TouchFront_Update();
	
		if (pressed_pad[PAD_SQUARE])
		{
			initImeDialog(language_container[FORECAST_KEYBOARD], "", 12, SCE_IME_TYPE_BASIC_LATIN, 0, 0);
			setDialogStep(DIALOG_STEP_FORECAST_ZIP);
		}else if (pressed_pad[PAD_CANCEL])
		{
			closeForeCastMenu();
	    }else if (TouchFront_CheckIsPressed()) 
		{
			if (!(TouchFront_GetX() >= 129 && TouchFront_GetX() <= 831 && TouchFront_GetY() >= 81 && TouchFront_GetY() <= 463))
				closeForeCastMenu();
		}
}