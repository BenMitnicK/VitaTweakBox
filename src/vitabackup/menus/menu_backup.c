#include "../vitabackup.h"

#include "../../theme.h"
#include "../../language.h"
#include "../../message_dialog.h"
#include "../../ime_dialog.h"
#include "../../utils.h"
#include "../../touch.h"

#define LIST_PER_PAGE  5
#define DISTANCE_Y     80
#define MAX_MENU_ITEMS2 255

static SceInt selection = 0;

static int n_Vitamenubackup_entries = 0;
static VitamenubackupMenu Vitamenubackup_menu;

char items[256][51];
char items_path[256][101];
static SceInt count = 0;

SceInt initServices(SceVoid){
	
	char line[256];

	SceUID file = 0;

	if (FS_FileExists("ur0:/data/VitaBackup/path.txt"))
		file = sceIoOpen("ur0:/data/VitaBackup/path.txt", SCE_O_RDONLY, 0);
	else
	{
		file = sceIoOpen("ur0:/data/VitaBackup/path.txt", SCE_O_WRONLY | SCE_O_CREAT | SCE_O_TRUNC, 0777); // Create default path file:
		char *buf = (char *)malloc(1024);
		
		SceInt len = snprintf(buf, 1024, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s", 
			"Encrypted savedata~ux0:/user/00/savedata",
			"Encrypted savedata_backup~ux0:/user/00/savedata_backup",
			"Encrypted savedata_plus~ux0:/user/00/savedata_plus",
			"Decrypted savedata~ux0:/data/savegames",
			"PSP savedata~ux0:/PSPEMU/PSP/SAVEDATA/",
			"Trophies~ux0:/user/00/trophy",
			"Trophies~ur0:/user/00/trophy",
			"System Settings and User Information~vd0:/registry",
			"User and Hardware IDs~ux0:/id.dat",
			"Licenses~ux0:/license",
			"Database~ur0:/shell/db/app.db",
			"Activation~tm0:/npdrm/act.dat");
		
		sceIoWrite(file, buf, len);
		
		free(buf);
		sceIoClose(file);

		file = sceIoOpen("ur0:/data/VitaBackup/path.txt", SCE_O_RDONLY, 0); // Now re-open in read mode.
	}

	while (FS_Gets(line, sizeof line, file) != NULL) 
	{
		sscanf(line, "%[^~]~%[^~]", items[count], items_path[count]);
		items_path[count][strcspn(items_path[count], "\r\n")] = 0; // Remove trailing new line from fgets.
		count++;
	}

	sceIoClose(file);
	
	return 0;
}

static SceBool enable[MAX_MENU_ITEMS2 + 1];

SceInt Menu_Backup(SceVoid)
{
	
	SceInt title_width = vita2d_pgf_text_width(font, 1.5f, language_container[SELECT_BACKUP_DATA]);
	SceInt instr_width = vita2d_pgf_text_width(font, 1.0f, language_container[PRESS_START_BACKUP_PROCESS]);

	float slide_y = Vitamenubackup_menu.cur_pos - SCREEN_HEIGHT;
	double scroll_length = (372.0 / ((double)count - 1.0));

		if (pressed_pad[PAD_ENTER])
		{
			if (!enable[selection]){
				enable[selection] = SCE_TRUE;
			}else{
				enable[selection] = SCE_FALSE;
			}
		}

		vita2d_draw_texture(scroll_bg, 922, 56+slide_y);

		pgf2_draw_text(ALIGN_CENTER(960, title_width), 20+slide_y, VITABACKUP_BACKUPMENU_TIITLE_TEXT_COLOR, 1.5f, language_container[SELECT_BACKUP_DATA]);
		pgf_draw_text(ALIGN_CENTER(960, instr_width), 510+slide_y, VITABACKUP_BACKUPMENU_TEXT_START_COLOR, language_container[PRESS_START_BACKUP_PROCESS]);

		SceInt printed = 0; // Print counter

		for (int i = 0; i < count + 1; i++)
		{
			if (printed == LIST_PER_PAGE)
				break;

			if (count > 5) 
				vita2d_draw_texture(scroll_pointer, 922, 56 + (scroll_length * selection)+slide_y); // can't go more than y = 428 or it will be out of bounds

			if (selection < LIST_PER_PAGE || i > (selection - LIST_PER_PAGE))
			{
				if (i == selection){
					vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full_selected : checkbox_empty_selected, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
					//vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full : checkbox_empty, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
				}else{
					vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full : checkbox_empty, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
					//vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full_selected : checkbox_empty_selected, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
				}
				pgf_draw_text(125, 85 + (DISTANCE_Y * printed)+slide_y, i == selection? VITABACKUP_BACKUPMENU_TEXT_SELECTED_COLOR : VITABACKUP_BACKUPMENU_TEXT_COLOR, items[i]);
				pgf_draw_text(125, (85 + (DISTANCE_Y * printed)) + 35+slide_y, i == selection? VITABACKUP_BACKUPMENU_TEXT_SELECTED_COLOR : VITABACKUP_BACKUPMENU_TEXT_COLOR, items_path[i]);

				printed++;
			}
		}
		
		if (pressed_pad[PAD_DOWN])
		{
			if (selection < (count - 1))
				selection++;
			else 
				selection = 0;
		}
		else if (pressed_pad[PAD_UP])
		{
			if (selection > 0)
				selection--;
			else 
				selection = (count - 1);
		}
		
		// Tests so far
		if (pressed_pad[PAD_START])
		{
			for (SceInt i = 0; i < count + 1; i++)
			{
				if (enable[i] == SCE_TRUE)
				{
					Utils_LockPower();
					MicrotarWrite_AddToTar(items_path[i]);
					Utils_UnlockPower();
				}		
			}
		}
	
	return 0;
}

void initVitamenubackupMenu() {
	memset(&Vitamenubackup_menu, 0, sizeof(VitamenubackupMenu));
	Vitamenubackup_menu.status = VITAMENUBACKUP_MENU_CLOSED;
	n_Vitamenubackup_entries = 1;
	initServices();
}

void openVitamenubackupMenu() {
	Vitamenubackup_menu.status = VITAMENUBACKUP_MENU_OPENING;
}

void closeVitamenubackupMenu() {
	Vitamenubackup_menu.status = VITAMENUBACKUP_MENU_CLOSING;
}

int getVitamenubackupMenuStatus() {
	return Vitamenubackup_menu.status;
}

void drawVitamenubackupMenu() {
  
	if (Vitamenubackup_menu.status == VITAMENUBACKUP_MENU_CLOSED)
		return;

	// Closing settings menu
	if (Vitamenubackup_menu.status == VITAMENUBACKUP_MENU_CLOSING) {
		if (Vitamenubackup_menu.cur_pos > 0.0f) {
			Vitamenubackup_menu.cur_pos -= easeOut(0.0f, Vitamenubackup_menu.cur_pos, 0.25f, 0.01f);
		} else {
			Vitamenubackup_menu.status = VITAMENUBACKUP_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (Vitamenubackup_menu.status == VITAMENUBACKUP_MENU_OPENING) {
		if (Vitamenubackup_menu.cur_pos < SCREEN_HEIGHT) {
			Vitamenubackup_menu.cur_pos += easeOut(Vitamenubackup_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			Vitamenubackup_menu.status = VITAMENUBACKUP_MENU_OPENED;
		}
		memset(enable, 0, sizeof(enable)); // Reset all enabled data
		selection = 0;
	}

	// Draw settings menu
	vita2d_draw_texture(vitabackup2_image, 0.0f, Vitamenubackup_menu.cur_pos - SCREEN_HEIGHT);
	
	if (Vitamenubackup_menu.cur_pos > 0.0f) {
		Menu_Backup();
	}
}

static int agreement = VITAMENUBACKUP_AGREEMENT_NONE;

void VitamenubackupAgree() {
	agreement = VITAMENUBACKUP_AGREEMENT_AGREE;
}

void VitamenubackupDisagree() {
	agreement = VITAMENUBACKUP_AGREEMENT_DISAGREE;
}

void VitamenubackupMenuCtrl() {
	TouchBack_Update();

	// Agreement
	if (agreement != VITAMENUBACKUP_AGREEMENT_NONE) {
		agreement = VITAMENUBACKUP_AGREEMENT_NONE;
	}
		
		if (pressed_pad[PAD_CANCEL]){
			closeVitamenubackupMenu();
			openVitabackupMenu();
		}else if (TouchBack_CheckIsPressed()) 
		{
			if (TouchBack_GetX() >= 0 && TouchBack_GetX() <= 960 && TouchBack_GetY() >= 0 && TouchBack_GetY() <= 220)
			{
				closeVitamenubackupMenu();
				openVitabackupMenu();
			}
		}
}
