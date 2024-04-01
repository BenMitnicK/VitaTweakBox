#ifndef __MENU_RESTORE_H__
#define __MENU_RESTORE_H__

#include "../../main.h"

enum VitarestoreAgreement {
	VITARESTORE_AGREEMENT_NONE,
	VITARESTORE_AGREEMENT_AGREE,
	VITARESTORE_AGREEMENT_DISAGREE,
};

enum VitarestoreOptionType {
	VITARESTORE_OPTION_TYPE_BOOLEAN,
	VITARESTORE_OPTION_TYPE_INTEGER,
	VITARESTORE_OPTION_TYPE_STRING,
	VITARESTORE_OPTION_TYPE_CALLBACK,
	VITARESTORE_OPTION_TYPE_NOTHING,
};

enum VitarestoreMenuStatus {
	VITARESTORE_MENU_CLOSED,
	VITARESTORE_MENU_CLOSING,
	VITARESTORE_MENU_OPENED,
	VITARESTORE_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} VitarestoreMenu;

void initVitarestoreMenu();
void openVitarestoreMenu();
void closeVitarestoreMenu();
int getVitarestoreMenuStatus();
void drawVitarestoreMenu();
void VitarestoreMenuCtrl();

void VitarestoreAgree();
void VitarestoreDisagree();

#endif