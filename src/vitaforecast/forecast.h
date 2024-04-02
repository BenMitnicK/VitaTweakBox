#ifndef _FORECAST_MAIN_H_
#define _FORECAST_MAIN_H_

#define selector_xDistance 0 //The distance between the X axis of the two selections
#define selector_yDistance 40 //The distance between the Y axis of the two selections

enum ForeCastAgreement {
	FORECAST_AGREEMENT_NONE,
	FORECAST_AGREEMENT_AGREE,
	FORECAST_AGREEMENT_DISAGREE,
};

enum ForeCastOptionType {
	FORECAST_OPTION_TYPE_BOOLEAN,
	FORECAST_OPTION_TYPE_INTEGER,
	FORECAST_OPTION_TYPE_STRING,
	FORECAST_OPTION_TYPE_CALLBACK,
	FORECAST_OPTION_TYPE_NOTHING,
};

enum ForeCastMenuStatus {
	FORECAST_MENU_CLOSED,
	FORECAST_MENU_CLOSING,
	FORECAST_MENU_OPENED,
	FORECAST_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} ForeCastMenu;

void initForeCastMenu();
void openForeCastMenu();
void closeForeCastMenu();
int getForeCastMenuStatus();
void drawForeCastMenu();
void ForeCastMenuCtrl();

void ForeCastAgree();
void ForeCastDisagree();

extern ForeCastMenu ForeCast_menu;
int sceLocationInit();
int sceLocationTerm();

void getLocation();

#endif
