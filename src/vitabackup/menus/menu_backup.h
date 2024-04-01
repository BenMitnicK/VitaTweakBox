#ifndef __MENU_BACKUP_H__
#define __MENU_BACKUP_H__

#include "../../main.h"

enum VitamenubackupAgreement {
	VITAMENUBACKUP_AGREEMENT_NONE,
	VITAMENUBACKUP_AGREEMENT_AGREE,
	VITAMENUBACKUP_AGREEMENT_DISAGREE,
};

enum VitamenubackupOptionType {
	VITAMENUBACKUP_OPTION_TYPE_BOOLEAN,
	VITAMENUBACKUP_OPTION_TYPE_INTEGER,
	VITAMENUBACKUP_OPTION_TYPE_STRING,
	VITAMENUBACKUP_OPTION_TYPE_CALLBACK,
	VITAMENUBACKUP_OPTION_TYPE_NOTHING,
};

enum VitamenubackupMenuStatus {
	VITAMENUBACKUP_MENU_CLOSED,
	VITAMENUBACKUP_MENU_CLOSING,
	VITAMENUBACKUP_MENU_OPENED,
	VITAMENUBACKUP_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} VitamenubackupMenu;

void initVitamenubackupMenu();
void openVitamenubackupMenu();
void closeVitamenubackupMenu();
int getVitamenubackupMenuStatus();
void drawVitamenubackupMenu();
void VitamenubackupMenuCtrl();

void VitamenubackupAgree();
void VitamenubackupDisagree();

#endif