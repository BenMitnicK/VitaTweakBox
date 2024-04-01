#include "../vitabackup.h"

#include "../../theme.h"
#include "../../language.h"
#include "../../message_dialog.h"
#include "../../ime_dialog.h"
#include "../../utils.h"
#include "../../touch.h"

#define MAX_MENU_ITEMS 255
#define LIST_PER_PAGE  5
#define DISTANCE_Y     80

#define wd ":data/VitaBackup/backups/"
#define wd2 ":VitaTweakBox/tweaks/Vitabackup/backups/"

typedef struct File
{
	struct File *next; // Next file
	SceBool isDir; // Folder flag
	char name[256]; // File name
} File;

static int n_Vitarestore_entries = 0;
static VitarestoreMenu Vitarestore_menu;

static SceInt selection = 0;
static SceInt fileCount = 0;
File *files = NULL;
char cwd[128];

// Free Heap Memory
static SceVoid Restore_RecursiveFree(File * node)
{
	if (node == NULL) 
		return;

	Restore_RecursiveFree(node->next);
	free(node);
}

static SceInt Restore_PopulateBackups(SceBool refresh)
{
	SceInt dir = 0;

	Restore_RecursiveFree(files);
	files = NULL;
	fileCount = 0;

	if(vitashell_config.backup_storage){
		snprintf(cwd, 50, "ur0%s", wd);
	}else{
		snprintf(cwd, 50, "ux0%s", wd2);
	}

	if (R_SUCCEEDED(dir = sceIoDopen(cwd)))
	{
		SceInt ret = 1;

		// Iterate Files
		while (ret > 0)
		{
			// File entry
			SceIoDirent entry;
			memset(&entry, 0, sizeof(entry));

			if (R_SUCCEEDED(ret = sceIoDread(dir, &entry)))
			{
				// Ingore null filename
				if (entry.d_name[0] == '\0') 
					continue;

				// Ignore "." in all directories
				if (strcmp(entry.d_name, ".") == 0) 
					continue;

				// Ignore ".." in all directories
				if (strcmp(entry.d_name, "..") == 0) 
					continue;

				// Allocate Memory
				File *item = (File *)malloc(sizeof(File));
				memset(item, 0, sizeof(File));

				// Copy File Name
				strcpy(item->name, entry.d_name);

				item->isDir = SCE_S_ISDIR(entry.d_stat.st_mode);

				// Ignore anything that is not a tar file
				char * ext = strrchr(item->name, '.');
				if (strcmp(ext, ".tar") != 0)
					continue;

				// New List
				if (files == NULL) 
					files = item;

				// Existing List
				else
				{
					File * list = files;
					
					while(list->next != NULL) 
						list = list->next;
					
					list->next = item;
				}

				fileCount++;
			}
			else
				return ret;
		}

		if (R_FAILED(ret = sceIoDclose(dir)))
			return ret;
	}
	else
		return dir;
	
	return 0;
}

static SceBool enable[MAX_MENU_ITEMS + 1];

static SceInt Restore_DisplayFiles(SceVoid)
{
	double scroll_length = (372.0 / ((double)fileCount - 1.0));
	float slide_y = Vitarestore_menu.cur_pos - SCREEN_HEIGHT;
	SceInt title_width = vita2d_pgf_text_width(font, 1.5f, language_container[SELECT_RESTORE_DATA]);
	SceInt instr_width = vita2d_pgf_text_width(font, 1.0f, language_container[PRESS_START_RESTORE_PROCESS]);

	vita2d_draw_texture(scroll_bg, 922, 56+slide_y);

	pgf2_draw_text(ALIGN_CENTER(960, title_width), 20+slide_y, VITABACKUP_RESTORE_TIITLE_TEXT_COLOR, 1.5f, language_container[SELECT_RESTORE_DATA]);
	pgf_draw_text(ALIGN_CENTER(960, instr_width), 510+slide_y, VITABACKUP_RESTORE_TEXT_START_COLOR, language_container[PRESS_START_RESTORE_PROCESS]);

	
	// File Iterator
	SceInt i = 0, printed = 0;

	// Draw File List
	File *file = files;
	
	for (; file != NULL; file = file->next)
	{
		// Limit the files per page
		if (printed == LIST_PER_PAGE) 
			break;

		if (fileCount > 5) // Draw scroll only if there are more than 5 objects on the screen
			vita2d_draw_texture(scroll_pointer, 922, 56 + (scroll_length * selection)+slide_y); // can't go more than y = 428 or it will be out of bounds

		if (selection < LIST_PER_PAGE || i > (selection - LIST_PER_PAGE))
		{
			if (i == selection)
				vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full_selected : checkbox_empty_selected, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
				//vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full : checkbox_empty, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
			else
				vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full : checkbox_empty, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);
				//vita2d_draw_texture(enable[i] == SCE_TRUE? checkbox_full_selected : checkbox_empty_selected, 50, (110 + (DISTANCE_Y * printed)) - 10+slide_y);

			char * ext = strrchr(file->name, '.');

			if (strncasecmp(ext ,".tar", 4) == 0)
				vita2d_draw_texture(i == selection? ico_container_zip_selected : ico_container_zip, 115, 86 + (DISTANCE_Y * printed)+slide_y);
			
			char buf[64], path[500], size[16];

			strncpy(buf, file->name, sizeof(buf));
			buf[sizeof(buf) - 1] = '\0';
			int len = strlen(buf);
			len = 40 - len;
			
			while (len -- > 0)
				strcat(buf, " ");

			pgf_draw_text(200, 85 + (DISTANCE_Y * printed)+slide_y, i == selection? VITABACKUP_RESTORE_TEXT_SELECTED_COLOR : VITABACKUP_RESTORE_TEXT_COLOR, buf); // printf file name

			strcpy(path, cwd);
			strcpy(path + strlen(path), file->name);
			char dateStr[16], timeStr[24];
			Utils_GetDateString(dateStr, 0, FS_GetFileModifiedTime(path), SCE_TRUE); // Get modified date
			Utils_GetTimeString(timeStr, 0, FS_GetFileModifiedTime(path)); // Get modified time
			
			char pathText[256];
			snprintf(pathText, 256, "%s %s - %s", dateStr, timeStr, size);
			
			if (!(file->isDir))
			{
				Utils2_GetSizeString(size, FS_GetFileSize(path)); // Get size for files only
				pgf_draw_text(200, (85 + (DISTANCE_Y * printed)) + 35+slide_y, i == selection? VITABACKUP_RESTORE_TEXT_SELECTED_COLOR : VITABACKUP_RESTORE_TEXT_COLOR, pathText);
			}

			printed++; // Increase printed counter
		}

		i++;
	}
	
	return 0;
}

static File *Restore_FindIndex(SceInt index)
{
	SceInt i = 0;
	File *file = files; 
	
	for(; file != NULL && i != index; file = file->next) 
		i++;

	return file;
}

SceInt Menu_Restore(SceVoid)
{

	Restore_PopulateBackups(SCE_TRUE);
	Restore_DisplayFiles();
	
	
		if (fileCount > 0)
		{
			if (pressed_pad[PAD_UP])
			{
				if (selection > 0){ 
					selection--;
				}else{
					selection = fileCount - 1;
				}
			}
			else if (pressed_pad[PAD_DOWN])
			{
				if (selection < (fileCount - 1)){
					selection++;
				}else{
					selection = 0;
				}
			}
		}

		if (pressed_pad[PAD_ENTER])
		{
			if (!enable[selection]){
				enable[selection] = SCE_TRUE;
			}else{
				enable[selection] = SCE_FALSE;
			}				
		} 
		
		if (pressed_pad[PAD_START])
		{
			for (SceInt i = 0; i < fileCount; i++)
			{
				if (enable[i] == SCE_TRUE)
				{
					File *file = Restore_FindIndex(i);
			
					char path[256], filename[256];
					strcpy(filename, file->name);
	
					strcpy(path, cwd);
					strcpy(path + strlen(path), file->name);
			
					Utils_LockPower();
					MicrotarRead_ExtractTar(path, "ux0:");
					Utils_UnlockPower();
				}
			}
			Restore_DisplayFiles();
		} 
		
		if (pressed_pad[PAD_SQUARE])
		{
			for (SceInt i = 0; i < fileCount; i++)
			{
				if (enable[i] == SCE_TRUE)
				{
					File *file = Restore_FindIndex(i);
			
					char path[256], filename[256];
					strcpy(filename, file->name);
	
					strcpy(path, cwd);
					strcpy(path + strlen(path), file->name);
			
					Utils_LockPower();
					//Menu_Delete(path);
					Utils_UnlockPower();
				}
			}
		}
	

	return 1;
}

void initVitarestoreMenu() {
	memset(&Vitarestore_menu, 0, sizeof(VitarestoreMenu));
	Vitarestore_menu.status = VITARESTORE_MENU_CLOSED;
	n_Vitarestore_entries = 1;
}

void openVitarestoreMenu() {
	Vitarestore_menu.status = VITARESTORE_MENU_OPENING;
}

void closeVitarestoreMenu() {
	Vitarestore_menu.status = VITARESTORE_MENU_CLOSING;
}

int getVitarestoreMenuStatus() {
	return Vitarestore_menu.status;
}

void drawVitarestoreMenu() {
  
	if (Vitarestore_menu.status == VITARESTORE_MENU_CLOSED)
		return;

	// Closing settings menu
	if (Vitarestore_menu.status == VITARESTORE_MENU_CLOSING) {
		if (Vitarestore_menu.cur_pos > 0.0f) {
			Vitarestore_menu.cur_pos -= easeOut(0.0f, Vitarestore_menu.cur_pos, 0.25f, 0.01f);
		} else {
			Vitarestore_menu.status = VITARESTORE_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (Vitarestore_menu.status == VITARESTORE_MENU_OPENING) {
		if (Vitarestore_menu.cur_pos < SCREEN_HEIGHT) {
			Vitarestore_menu.cur_pos += easeOut(Vitarestore_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			Vitarestore_menu.status = VITARESTORE_MENU_OPENED;
		}
		memset(enable, 0, sizeof(enable)); // Reset all enabled data
		selection = 0;
	}

	// Draw settings menu
	vita2d_draw_texture(vitarestore_image, 0.0f, Vitarestore_menu.cur_pos - SCREEN_HEIGHT);
	
	if (Vitarestore_menu.cur_pos > 0.0f) {
		Menu_Restore();
	}
}

static int agreement = VITARESTORE_AGREEMENT_NONE;

void VitarestoreAgree() {
	agreement = VITARESTORE_AGREEMENT_AGREE;
}

void VitarestoreDisagree() {
	agreement = VITARESTORE_AGREEMENT_DISAGREE;
}

void VitarestoreMenuCtrl() {
	TouchBack_Update();

	// Agreement
	if (agreement != VITARESTORE_AGREEMENT_NONE) {
		agreement = VITARESTORE_AGREEMENT_NONE;
	}

		if (pressed_pad[PAD_CANCEL]){
			closeVitarestoreMenu();
			openVitabackupMenu();
		}else if (TouchBack_CheckIsPressed()) 
		{
			if (TouchBack_GetX() >= 0 && TouchBack_GetX() <= 960 && TouchBack_GetY() >= 0 && TouchBack_GetY() <= 220)
			{
				closeVitarestoreMenu();
				openVitabackupMenu();
			}
		}
}
