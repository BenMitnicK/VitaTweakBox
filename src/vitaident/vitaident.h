#ifndef _VITAIDENT_H_
#define _VITAIDENT_H_

#include "app.h"
#include "kernel.h"
#include "net.h"
#include "power.h"
#include "regmgr.h"
#include "vitaident_utils.h"

#include "../main.h"

#define selector_xDistance 0 //The distance between the X axis of the two selections
#define selector_yDistance 40 //The distance between the Y axis of the two selections

enum VitaidentAgreement {
	VITAIDENT_AGREEMENT_NONE,
	VITAIDENT_AGREEMENT_AGREE,
	VITAIDENT_AGREEMENT_DISAGREE,
};

enum VitaidentOptionType {
	VITAIDENT_OPTION_TYPE_BOOLEAN,
	VITAIDENT_OPTION_TYPE_INTEGER,
	VITAIDENT_OPTION_TYPE_STRING,
	VITAIDENT_OPTION_TYPE_CALLBACK,
	VITAIDENT_OPTION_TYPE_NOTHING,
};

enum VitaidentMenuStatus {
	VITAIDENT_MENU_CLOSED,
	VITAIDENT_MENU_CLOSING,
	VITAIDENT_MENU_OPENED,
	VITAIDENT_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} VitaidentMenu;

void initVitaidentMenu();
void openVitaidentMenu();
void closeVitaidentMenu();
int getVitaidentMenuStatus();
void drawVitaidentMenu();
void VitaidentMenuCtrl();

void VitaidentAgree();
void VitaidentDisagree();

#endif