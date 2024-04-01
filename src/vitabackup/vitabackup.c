#include "vitabackup.h"
#include "../main.h"
#include "../config.h"
#include "../init.h"
#include "../theme.h"
#include "../language.h"
#include "../message_dialog.h"
#include "../ime_dialog.h"
#include "../utils.h"
#include "../touch.h"

#define MAX_MENU_ITEMS 1

static SceInt selection = 0;

static int n_Vitabackup_entries = 0;
static VitabackupMenu Vitabackup_menu;

void initVitabackupMenu() {
	memset(&Vitabackup_menu, 0, sizeof(VitabackupMenu));
	Vitabackup_menu.status = VITABACKUP_MENU_CLOSED;
	n_Vitabackup_entries = 1;
}

void openVitabackupMenu() {
	Vitabackup_menu.status = VITABACKUP_MENU_OPENING;
}

void closeVitabackupMenu() {
	Vitabackup_menu.status = VITABACKUP_MENU_CLOSING;
}

int getVitabackupMenuStatus() {
	return Vitabackup_menu.status;
}

static SceVoid Init_Services(SceVoid)
{
	
	if (!FS_DirExists("ur0:/data/VitaBackup/backups"))
		FS_RecursiveMakeDir("ur0:/data/VitaBackup/backups");

	if (FS_FileExists("ux0:VitaTweakBox/tweaks/Vitabackup/log.txt")) // Start a new log file on boot.
		FS_RemoveFile("ux0:VitaTweakBox/tweaks/Vitabackup/log.txt");

	Options_LoadConfig();

}

SceVoid Menu_Main(SceVoid)
{
	uint32_t vitabackup_eC = epileptik4();
	unsigned int icon_width = vita2d_texture_get_width(ico_main_backup); // 120
	unsigned int icon_height = vita2d_texture_get_height(ico_main_backup);
	float slide_y = (Vitabackup_menu.cur_pos - 373) + 20;
	float _x;
	
	vita2d_draw_texture(ico_main_backup, ALIGN_CENTER(192, icon_width)+288, slide_y);
	vita2d_draw_texture(ico_main_restore, ALIGN_CENTER(192, icon_width)+480, slide_y);
	
	vita2d_draw_fill_circle(384, 60+slide_y, 55, selection == 0? RGBA8(VITABACKUP_MENU_R, VITABACKUP_MENU_G, VITABACKUP_MENU_B, vitabackup_eC) : RGBA8(0, 0, 0, 0));
	vita2d_draw_fill_circle(576, 60+slide_y, 55, selection == 1? RGBA8(VITABACKUP_MENU_R, VITABACKUP_MENU_G, VITABACKUP_MENU_B, vitabackup_eC) : RGBA8(0, 0, 0, 0));

	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[BACKUP_MENU]);
	pgf_draw_text(ALIGN_CENTER(192, _x)+288, 20+icon_height+slide_y, VITABACKUP_TEXT_COLOR, language_container[BACKUP_MENU]);
	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[RESTORE_MENU]);
	pgf_draw_text(ALIGN_CENTER(192, _x)+480, 20+icon_height+slide_y, VITABACKUP_TEXT_COLOR, language_container[RESTORE_MENU]);
}

void drawVitabackupMenu() {
  
	if (Vitabackup_menu.status == VITABACKUP_MENU_CLOSED)
		return;

	// Closing settings menu
	if (Vitabackup_menu.status == VITABACKUP_MENU_CLOSING) {
		if (Vitabackup_menu.cur_pos > 0.0f) {
			Vitabackup_menu.cur_pos -= easeOut(0.0f, Vitabackup_menu.cur_pos, 0.25f, 0.01f);
		} else {
			Vitabackup_menu.status = VITABACKUP_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (Vitabackup_menu.status == VITABACKUP_MENU_OPENING) {
		if (Vitabackup_menu.cur_pos < SCREEN_HEIGHT) {
			Vitabackup_menu.cur_pos += easeOut(Vitabackup_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			Vitabackup_menu.status = VITABACKUP_MENU_OPENED;
		}
	}

	// Draw settings menu
	vita2d_draw_texture(vitabackup_image, 254, Vitabackup_menu.cur_pos - 373);
	
	if (Vitabackup_menu.cur_pos > 0.0f) {
		Init_Services();
		Menu_Main();
	}
}

static int agreement = VITABACKUP_AGREEMENT_NONE;

void VitabackupAgree() {
	agreement = VITABACKUP_AGREEMENT_AGREE;
}

void VitabackupDisagree() {
	agreement = VITABACKUP_AGREEMENT_DISAGREE;
}

static void menuBackupMenu_HandleTouch()
{
	if (TouchFront_CheckIsReleased()) 
	{
		if (TouchFront_GetX() >= 329 && TouchFront_GetX() <= 439 && TouchFront_GetY() >= 196 && TouchFront_GetY() <= 306){
			selection = 0;
		}
		else if (TouchFront_GetX() >= 521 && TouchFront_GetX() <= 631 && TouchFront_GetY() >= 196 && TouchFront_GetY() <= 306){
			selection = 1;
		}
	}
	
	if (TouchFront_CheckIsPressed()) 
	{
		if (selection == 0 && (TouchFront_GetX() >= 329 && TouchFront_GetX() <= 439 && TouchFront_GetY() >= 196 && TouchFront_GetY() <= 306)){
			closeVitabackupMenu();
			openVitamenubackupMenu();
		}
		else if (selection == 1 && (TouchFront_GetX() >= 521 && TouchFront_GetX() <= 631 && TouchFront_GetY() >= 196 && TouchFront_GetY() <= 306)){
			closeVitabackupMenu();
			openVitarestoreMenu();
		}
	}
}

void VitabackupMenuCtrl() {

	// Agreement
	if (agreement != VITABACKUP_AGREEMENT_NONE) {
		agreement = VITABACKUP_AGREEMENT_NONE;
	}

	TouchFront_Update();
		
		if (pressed_pad[PAD_RIGHT])
			selection++;
		else if (pressed_pad[PAD_LEFT])
			selection--;
		
		if (selection > MAX_MENU_ITEMS)
			selection = 0;
		if (selection < 0)
			selection = MAX_MENU_ITEMS;

		if (pressed_pad[PAD_ENTER])
		{
			switch (selection)
			{
				case 0:
					closeVitabackupMenu();
					openVitamenubackupMenu();
					break;
				case 1:
					closeVitabackupMenu();
					openVitarestoreMenu();
					break;
			}
		}
		
		menuBackupMenu_HandleTouch();
		
		if (pressed_pad[PAD_CANCEL]){
			closeVitabackupMenu();
		}else if (TouchFront_CheckIsPressed()) 
		{
			if (!(TouchFront_GetX() >= 254 && TouchFront_GetX() <= 706 && TouchFront_GetY() >= 171 && TouchFront_GetY() <= 373))
				closeVitabackupMenu();
		}
		
}
