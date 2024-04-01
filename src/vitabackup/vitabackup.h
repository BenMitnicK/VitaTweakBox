#ifndef __VITABACKUP_H__
#define __VITABACKUP_H__

#include "fs.h"
#include "log.h"
#include "progress_bar.h"
#include "vitabackup_utils.h"
#include "menus/menu_options.h"
#include "menus/menu_backup.h"
//#include "menus/menu_delete.h"
#include "menus/menu_restore.h"
#include "microtar/microtar.h"
#include "microtar/microtar_read.h"
#include "microtar/microtar_write.h"

#include "../main.h"

#define vita2d_end_frame() {		\
	vita2d_end_drawing();			\
	vita2d_common_dialog_update();	\
	vita2d_swap_buffers();			\
	sceDisplayWaitVblankStart();	\
}

enum VitabackupAgreement {
	VITABACKUP_AGREEMENT_NONE,
	VITABACKUP_AGREEMENT_AGREE,
	VITABACKUP_AGREEMENT_DISAGREE,
};

enum VitabackupOptionType {
	VITABACKUP_OPTION_TYPE_BOOLEAN,
	VITABACKUP_OPTION_TYPE_INTEGER,
	VITABACKUP_OPTION_TYPE_STRING,
	VITABACKUP_OPTION_TYPE_CALLBACK,
	VITABACKUP_OPTION_TYPE_NOTHING,
};

enum VitabackupMenuStatus {
	VITABACKUP_MENU_CLOSED,
	VITABACKUP_MENU_CLOSING,
	VITABACKUP_MENU_OPENED,
	VITABACKUP_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} VitabackupMenu;

void initVitabackupMenu();
void openVitabackupMenu();
void closeVitabackupMenu();
int getVitabackupMenuStatus();
void drawVitabackupMenu();
void VitabackupMenuCtrl();

void VitabackupAgree();
void VitabackupDisagree();

#endif