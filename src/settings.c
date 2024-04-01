/*
  VitaShell/VitaTweakBox
  Copyright (C) 2015-2018, TheFloW Modded By BenMitnicK

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "main.h"
#include "config.h"
#include "init.h"
#include "theme.h"
#include "language.h"
#include "settings.h"
#include "vitabackup/menus/menu_options.h" //BMK
#include "loadimages.h"
#include "message_dialog.h"
#include "ime_dialog.h"
#include "utils.h"
#include "touch.h"
#include "file.h"

/////////////// BMK ////////////////
#define MAX_MENU_ITEMS 3

static int count = 0;
static int NavOffset = 0;

int themefound = 0;	

int value; // 1 for power menu and 0 settings menu
static SceInt selection = 0;

static char **themeImagesPatch_options = NULL;
static char **themeImagesType_options = NULL;
static vita2d_texture *tex = NULL;
static int type;
static int themePreview_count;
static char patch[MAX_PATH_LENGTH];
////////////////////////////////////

static void restartShell();
static void rebootDevice();
static void shutdownDevice();
static void suspendDevice();

static int changed = 0;
static int theme = 0;

static char spoofed_version[6];

static SettingsMenuEntry *settings_menu_entries = NULL;
static int n_settings_entries = 0;

static char *usbdevice_options[4];
static char *select_button_options[2];

static char **theme_options = NULL;
static int theme_count = 0;
static char *theme_name = NULL;

/////////////// BMK ////////////////
static char *select_lang_options[19];
static char select_theme_options[256] = "";
char themeActual[256] = "";
////////////////////////////////////

static ConfigEntry settings_entries[] = {
  { "USBDEVICE",          CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.usbdevice },
  { "SELECT_BUTTON",      CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.select_button },
  /////////////// BMK ////////////////
  { "LANGUAGE", CONFIG_TYPE_DECIMAL, (int *)&vitashell_config.select_lang },
  { "BACKUP_STORAGE", CONFIG_TYPE_BOOLEAN, (int *)&vitashell_config.backup_storage },
  ////////////////////////////////////
  { "DISABLE_AUTOUPDATE", CONFIG_TYPE_BOOLEAN, (int *)&vitashell_config.disable_autoupdate },
  { "DISABLE_WARNING",    CONFIG_TYPE_BOOLEAN, (int *)&vitashell_config.disable_warning },
};

static ConfigEntry theme_entries[] = {
  { "THEME_NAME", CONFIG_TYPE_STRING, (void *)&theme_name },
};

SettingsMenuOption main_settings[] = {
  
  /////////////// BMK ////////////////
  { VITASHELL_SETTINGS_THEME,				SETTINGS_OPTION2_TYPE_STRING, NULL, select_theme_options, sizeof(select_theme_options), NULL },
  
  { VITASHELL_SETTINGS_LANGUAGE,			SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0, 
											select_lang_options, sizeof(select_lang_options) / sizeof(char **), 
											&vitashell_config.select_lang },
  ////////////////////////////////////
  
  { VITASHELL_SETTINGS_USBDEVICE,       SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0,
    usbdevice_options, sizeof(usbdevice_options) / sizeof(char **), &vitashell_config.usbdevice },
  { VITASHELL_SETTINGS_SELECT_BUTTON,   SETTINGS_OPTION_TYPE_OPTIONS, NULL, NULL, 0,
    select_button_options, sizeof(select_button_options) / sizeof(char **), &vitashell_config.select_button },
	
  /////////////// BMK ////////////////
  { VITASHELL_SETTINGS_BACKUP_STORAGE,  SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.backup_storage },
  ////////////////////////////////////
  
  { VITASHELL_SETTINGS_NO_AUTO_UPDATE,  SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.disable_autoupdate },
  { VITASHELL_SETTINGS_WARNING_MESSAGE, SETTINGS_OPTION_TYPE_BOOLEAN, NULL, NULL, 0, NULL, 0, &vitashell_config.disable_warning },
  
};

SettingsMenuEntry vitashell_settings_menu_entries[] = {
  { VITASHELL_SETTINGS_MAIN,  main_settings,  sizeof(main_settings) / sizeof(SettingsMenuOption) },
};

static SettingsMenu settings_menu;

void loadSettingsConfig() {
  // Load settings config file
  memset(&vitashell_config, 0, sizeof(VitaShellConfig));
  readConfig("ux0:VitaTweakBox/settings.txt", settings_entries, sizeof(settings_entries) / sizeof(ConfigEntry));
}

void saveSettingsConfig() {
  // Save settings config file
  writeConfig("ux0:VitaTweakBox/settings.txt", settings_entries, sizeof(settings_entries) / sizeof(ConfigEntry));

  if (sceKernelGetModel() == SCE_KERNEL_MODEL_VITATV) {
    vitashell_config.select_button = SELECT_BUTTON_MODE_FTP;
  }
}

static void restartShell() {
  closeSettingsMenu();
  sceAppMgrLoadExec("app0:eboot.bin", NULL, NULL);
}

static void rebootDevice() {
  closeSettingsMenu();
  scePowerRequestColdReset();
}

static void shutdownDevice() {
  closeSettingsMenu();
  scePowerRequestStandby();
}

static void suspendDevice() {
  closeSettingsMenu();
  scePowerRequestSuspend();
}

/////////////// BMK ////////////////
static int check_for_theme_preview_content(char *path) {
	SceUID dfd = sceIoDopen(path);

	if (dfd >= 0) {
		int res = 0;
		int i = 0;	
		int covercount = 0;
		
		do {
			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));
			res = sceIoDread(dfd, &dir);
			if (res > 0) {				
					if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0)
						continue;
					
					if(strcmp(dir.d_name, "preview.png") == 0){
						strncpy(themeImagesType_options[themePreview_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(themeImagesPatch_options[themePreview_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "Preview.png") == 0){
						strncpy(themeImagesType_options[themePreview_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(themeImagesPatch_options[themePreview_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "preview.jpg") == 0){
						strncpy(themeImagesType_options[themePreview_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(themeImagesPatch_options[themePreview_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "Preview.jpg") == 0){
						strncpy(themeImagesType_options[themePreview_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(themeImagesPatch_options[themePreview_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}
					
					i++;	
				}
		} while (res > 0);
		
		if (!covercount){
			snprintf(patch, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/no_preview.png", themeActual);
			if (checkFileExist(patch)){
				strncpy(themeImagesType_options[themePreview_count], "no_preview.png", MAX_PATH_LENGTH);
				strncpy(themeImagesPatch_options[themePreview_count], patch, MAX_PATH_LENGTH);
			}else{
				strncpy(themeImagesType_options[themePreview_count], "no_preview.png", MAX_PATH_LENGTH);
				strncpy(themeImagesPatch_options[themePreview_count], "ux0:VitaTweakBox/theme/Default/vtb/no_preview.png", MAX_PATH_LENGTH);
			}
		}
		covercount = 0;
		sceIoDclose(dfd);
	}

	return 0;
}

int check_for_theme_content(char *path) {
	SceUID dfd = sceIoDopen(path);
	
	if (dfd >= 0) {
		int res = 0;
		int i = 0;	
		theme_count = 0;
		
		do {
			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));
			res = sceIoDread(dfd, &dir);
			if (res > 0) {
				if (SCE_S_ISDIR(dir.d_stat.st_mode)) {
					if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0)
						continue;
					
					strncpy(theme_options[theme_count], dir.d_name, MAX_THEME_LENGTH);
					i++;	
					theme_count++;
					}
				}
		} while (res > 0 && theme_count < MAX_THEMES);
		count = i;	
		sceIoDclose(dfd);
		return count;
	}

	return 0;
}

void loadPreview(){
	
	NavOffset = 0;
	type = getFileType(themeImagesType_options[NavOffset]);
	tex = loadImages(themeImagesPatch_options[NavOffset], type);
	float rW = 563;
	float rH = 323;
	int res =0;
	char param[MAX_PATH_LENGTH];
	snprintf(param, MAX_PATH_LENGTH, "0.%d", SCALE_X_POSITION);
	float Scale_x = atof(param);
	snprintf(param, MAX_PATH_LENGTH, "0.%d", SCALE_Y_POSITION);
	float Scale_y = atof(param);
	snprintf(param, MAX_PATH_LENGTH, "1.%d", NAME_SIZE);
	float Size_text = atof(param);
	
		while (1) {
			
		  readPad();
		  TouchFront_Update();
		  TouchBack_Update();
		  
		  if (pressed_pad[PAD_SQUARE]){
		    
			theme_entries[0].value = &theme_options[NavOffset];
			writeConfig("ux0:VitaTweakBox/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));
			theme_entries[0].value = (void *)&theme_name;
			closeSettingsMenu();
			restartShell();
		    
		  }else if (pressed_pad[PAD_TRIANGLE]){
			  
			  break;
		  }else if (pressed_pad[PAD_LEFT] || hold_pad[PAD_LEFT]) {
			if(NavOffset > 0){
				NavOffset--;	
			
				type = getFileType(themeImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(themeImagesPatch_options[NavOffset], type);
				}
			}
		  }else if(pressed_pad[PAD_RIGHT] || hold_pad[PAD_RIGHT]){
			if(NavOffset < count-1){
				NavOffset++;

				type = getFileType(themeImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(themeImagesPatch_options[NavOffset], type);
				}
			}
		  }		
		
		if (TouchFront_CheckIsPressed()) 
		{
			if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 90 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
				if(NavOffset > 0){
					NavOffset--;	
			
				type = getFileType(themeImagesType_options[NavOffset]);
					if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
						vita2d_wait_rendering_done();
						vita2d_free_texture(tex);
						
						tex = loadImages(themeImagesPatch_options[NavOffset], type);
					}
				}
			}
			else if (TouchFront_GetX() >= 870 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
				if(NavOffset < count-1){
					NavOffset++;

				type = getFileType(themeImagesType_options[NavOffset]);
					if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
						vita2d_wait_rendering_done();
						vita2d_free_texture(tex);
						
						tex = loadImages(themeImagesPatch_options[NavOffset], type);
					}
				}
			}
		}else if (TouchBack_CheckIsPressed()) 
		{
			if (TouchBack_GetX() >= 0 && TouchBack_GetX() <= 960 && TouchBack_GetY() >= 0 && TouchBack_GetY() <= 220)
				break;
		}
		
		// Start drawing
		startDrawing(bg_select_theme_image);

		vita2d_draw_texture_scale(tex, PREVIEW_X_POSITION, PREVIEW_Y_POSITION, Scale_x, Scale_y);

		if(FILTER_ACTIVE == 1)
		vita2d_draw_rectangle(PREVIEW_X_POSITION, PREVIEW_Y_POSITION, FILTER_RW, FILTER_RH, RGBA8(FILTER_R_COLOR,FILTER_G_COLOR,FILTER_B_COLOR,FILTER_A_COLOR));    

		float _x = vita2d_pgf_text_width(font, Size_text, theme_options[NavOffset]);
		float _y = vita2d_pgf_text_height(font, Size_text, theme_options[NavOffset]);
		pgf2_draw_text(NAME_X_POSITION+ALIGN_CENTER(NAME_CENTER_DIM, _x), NAME_Y_POSITION, THEMEMANAGER_ITEM_COLOR, Size_text, theme_options[NavOffset]);
		
		if (TouchFront_CheckIsReleased())
		{
			if (TouchFront_GetX() >= NAME_X_POSITION+ALIGN_CENTER(NAME_CENTER_DIM, _x) && TouchFront_GetX() <= NAME_X_POSITION+ALIGN_CENTER(NAME_CENTER_DIM, _x)+_x && TouchFront_GetY() >= NAME_Y_POSITION && TouchFront_GetY() <= NAME_Y_POSITION+_y){
				theme_entries[0].value = &theme_options[NavOffset];
				writeConfig("ux0:VitaTweakBox/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));
				theme_entries[0].value = (void *)&theme_name;
				closeSettingsMenu();
				restartShell();
			}
		}
		
		float x_preview = vita2d_texture_get_width(tex);
		float y_preview = vita2d_texture_get_height(tex);
		
		if (TouchFront_CheckIsHold()) 
		{
			if (TouchFront_GetX() >= PREVIEW_X_POSITION && TouchFront_GetX() <= PREVIEW_X_POSITION+(x_preview * Scale_x) && TouchFront_GetY() >= PREVIEW_Y_POSITION && TouchFront_GetY() <= PREVIEW_Y_POSITION+(y_preview * Scale_y)){
				vita2d_draw_texture_scale(tex, 0, 0, 1, 1);
			}
		}
		
		// End drawing
		endDrawing();
		
		}
}
////////////////////////////////////

void initSettingsMenu() {
  int i;

  memset(&settings_menu, 0, sizeof(SettingsMenu));
  settings_menu.status = SETTINGS_MENU_CLOSED;

  n_settings_entries = sizeof(vitashell_settings_menu_entries) / sizeof(SettingsMenuEntry);
  settings_menu_entries = vitashell_settings_menu_entries;

  for (i = 0; i < n_settings_entries; i++)
    settings_menu.n_options += settings_menu_entries[i].n_options;

  usbdevice_options[0] = language_container[VITASHELL_SETTINGS_USB_MEMORY_CARD];
  usbdevice_options[1] = language_container[VITASHELL_SETTINGS_USB_GAME_CARD];
  usbdevice_options[2] = language_container[VITASHELL_SETTINGS_USB_SD2VITA];
  usbdevice_options[3] = language_container[VITASHELL_SETTINGS_USB_PSVSD];

  select_button_options[0] = language_container[VITASHELL_SETTINGS_SELECT_BUTTON_USB];
  select_button_options[1] = language_container[VITASHELL_SETTINGS_SELECT_BUTTON_FTP];
  
  readConfig("ux0:VitaTweakBox/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));
  strcpy(themeActual, theme_name);
  
  theme_options = malloc(MAX_THEMES * sizeof(char *));
  themeImagesType_options = malloc(MAX_THEMES * sizeof(char *));
  themeImagesPatch_options = malloc(MAX_THEMES * sizeof(char *));
  
  for (i = 0; i < MAX_THEMES; i++){
    theme_options[i] = malloc(MAX_THEME_LENGTH);
	themeImagesType_options[i] = malloc(MAX_PATH_LENGTH);
	themeImagesPatch_options[i] = malloc(MAX_PATH_LENGTH);
  }

	/////////////// BMK ////////////////	
	select_lang_options[0]  = language_container[english_us];
	select_lang_options[1]  = language_container[japanese];
	select_lang_options[2]  = language_container[french];
	select_lang_options[3]  = language_container[spanish];
	select_lang_options[4]  = language_container[german];
	select_lang_options[5]  = language_container[italian];
	select_lang_options[6]  = language_container[dutch];
	select_lang_options[7]  = language_container[portuguese];
	select_lang_options[8]  = language_container[russian];
	select_lang_options[9]  = language_container[korean];
	select_lang_options[10] = language_container[chinese_t];
	select_lang_options[11] = language_container[chinese_s];
	select_lang_options[12] = language_container[finnish];
	select_lang_options[13] = language_container[swedish];
	select_lang_options[14] = language_container[danish];
	select_lang_options[15] = language_container[norwegian];
	select_lang_options[16] = language_container[polish];
	select_lang_options[17] = language_container[portuguese_br];
	select_lang_options[18] = language_container[turkish];
	////////////////////////////////////
	
	themefound = check_for_theme_content("ux0:VitaTweakBox/theme/");
	
	for (themePreview_count = 0; themePreview_count < count; themePreview_count++){
		snprintf(patch, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/", theme_options[themePreview_count]);
		check_for_theme_preview_content(patch);
	}	
}

void openSettingsMenu() {
  settings_menu.status = SETTINGS_MENU_OPENING;
  settings_menu.entry_sel = 0;
  settings_menu.option_sel = 0;

  /////////////// BMK ////////////////
	// Get current theme
	if (theme_name)
		free(theme_name);
	
	readConfig("ux0:VitaTweakBox/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));
	strcpy(select_theme_options, theme_name);
  ////////////////////////////////////

  changed = 0;
}

void closeSettingsMenu() {
  settings_menu.status = SETTINGS_MENU_CLOSING;
  
  // Save settings
  if (changed) {
    saveSettingsConfig();
  }
}

int getSettingsMenuStatus() {
  return settings_menu.status;
}

SceVoid menu_Power(SceVoid)
{
	uint32_t power_eC = epileptik3();
	unsigned int icon_width = vita2d_texture_get_width(ico_menupower_shutdown); // 120
	unsigned int icon_height = vita2d_texture_get_height(ico_menupower_shutdown);
	float slide_y = (settings_menu.cur_pos - 385) + 30;
	float _x;
						
	vita2d_draw_texture(ico_menupower_shutdown, ALIGN_CENTER(160, icon_width)+160, slide_y);
	vita2d_draw_texture(ico_menupower_reboot, ALIGN_CENTER(160, icon_width)+320, slide_y);
	vita2d_draw_texture(ico_menupower_standby, ALIGN_CENTER(160, icon_width)+480, slide_y);		
	vita2d_draw_texture(ico_menupower_vtb_restart, ALIGN_CENTER(160, icon_width)+640, slide_y);
						
	vita2d_draw_fill_circle(240, 60+slide_y, 55, selection == 0? RGBA8(POWER_MENU_R, POWER_MENU_G, POWER_MENU_B, power_eC) : RGBA8(0, 0, 0, 0));
	vita2d_draw_fill_circle(400, 60+slide_y, 55, selection == 1? RGBA8(POWER_MENU_R, POWER_MENU_G, POWER_MENU_B, power_eC) : RGBA8(0, 0, 0, 0));
	vita2d_draw_fill_circle(560, 60+slide_y, 55, selection == 2? RGBA8(POWER_MENU_R, POWER_MENU_G, POWER_MENU_B, power_eC) : RGBA8(0, 0, 0, 0));
	vita2d_draw_fill_circle(720, 60+slide_y, 55, selection == 3? RGBA8(POWER_MENU_R, POWER_MENU_G, POWER_MENU_B, power_eC) : RGBA8(0, 0, 0, 0));
		
	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VITASHELL_SETTINGS_POWEROFF]);
	pgf_draw_text(ALIGN_CENTER(160, _x)+160, 20+icon_height+slide_y, POWERMENU_SHUTDOWN_COLOR, language_container[VITASHELL_SETTINGS_POWEROFF]);
	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VITASHELL_SETTINGS_REBOOT]);
	pgf_draw_text(ALIGN_CENTER(160, _x)+320, 20+icon_height+slide_y, POWERMENU_REBOOT_COLOR, language_container[VITASHELL_SETTINGS_REBOOT]);
	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VITASHELL_SETTINGS_STANDBY]);
	pgf_draw_text(ALIGN_CENTER(160, _x)+480, 20+icon_height+slide_y, POWERMENU_STANDBY_COLOR, language_container[VITASHELL_SETTINGS_STANDBY]);
	_x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VITASHELL_SETTINGS_RESTART_SHELL]);
	pgf_draw_text(ALIGN_CENTER(160, _x)+640, 20+icon_height+slide_y, POWERMENU_VTB_REBOOT_COLOR, language_container[VITASHELL_SETTINGS_RESTART_SHELL]);
}

void drawSettingsMenu() {
	
  if (settings_menu.status == SETTINGS_MENU_CLOSED)
    return;

  // Closing settings menu
  if (settings_menu.status == SETTINGS_MENU_CLOSING) {
    if (settings_menu.cur_pos > 0.0f) {
      settings_menu.cur_pos -= easeOut(0.0f, settings_menu.cur_pos, 0.25f, 0.01f);
    } else {
      settings_menu.status = SETTINGS_MENU_CLOSED;
    }
  }

  // Opening settings menu
  if (settings_menu.status == SETTINGS_MENU_OPENING) {
    if (settings_menu.cur_pos < SCREEN_HEIGHT) {
      settings_menu.cur_pos += easeOut(settings_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
    } else {
      settings_menu.status = SETTINGS_MENU_OPENED;
    }
  }

  // Draw settings menu
  vita2d_draw_texture(settings_image, 34, settings_menu.cur_pos - 385);

  if(value){ menu_Power(); }else{
  float y = (settings_menu.cur_pos - 385) + 10;

  int i;
  for (i = 0; i < n_settings_entries; i++) {
    // Title
    float x = pgf_text_width(language_container[settings_menu_entries[i].name]);
    pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), y, SETTINGS_MENU_TITLE_COLOR, language_container[settings_menu_entries[i].name]);

    y += FONT_Y_SPACE;

    SettingsMenuOption *options = settings_menu_entries[i].options;

    int j;
    for (j = 0; j < settings_menu_entries[i].n_options; j++) {
      // Focus
      if (settings_menu.entry_sel == i && settings_menu.option_sel == j)
        vita2d_draw_rectangle(SHELL_MARGIN_X+25, y + 3.0f, MARK_WIDTH-50, FONT_Y_SPACE, SETTINGS_MENU_FOCUS_COLOR);

      if (options[j].type == SETTINGS_OPTION_TYPE_CALLBACK) {
        // Item
        float x = pgf_text_width(language_container[options[j].name]);
        pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), y, SETTINGS_MENU_ITEM_COLOR, language_container[options[j].name]);
      } else {
        // Item
        float x = pgf_text_width(language_container[options[j].name]);
        pgf_draw_text(ALIGN_RIGHT(SCREEN_HALF_WIDTH - 10.0f, x), y, SETTINGS_MENU_ITEM_COLOR, language_container[options[j].name]);

        // Option
        switch (options[j].type) {
          case SETTINGS_OPTION_TYPE_BOOLEAN:
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR,
                          (options[j].value && *(options[j].value)) ? language_container[ON] : language_container[OFF]);
            break;

          case SETTINGS_OPTION_TYPE_STRING:
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR, options[j].string);
            break;

          case SETTINGS_OPTION_TYPE_OPTIONS:
          {
            int value = 0;
            if (options[j].value)
              value = *(options[j].value);
            pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR, options[j].options ? options[j].options[value] : "");
            break;
          }
		  /////////////// BMK ////////////////
		  	case SETTINGS_OPTION2_TYPE_STRING:
		  	pgf_draw_text(SCREEN_HALF_WIDTH + 10.0f, y, SETTINGS_MENU_OPTION_COLOR, options[j].string);
		  	break;	
		  ////////////////////////////////////
        }
      }

      y += FONT_Y_SPACE;
    }

    y += FONT_Y_SPACE;
  }
  }
}

static int agreement = SETTINGS_AGREEMENT_NONE;

void settingsAgree() {
  agreement = SETTINGS_AGREEMENT_AGREE;
}

void settingsDisagree() {
  agreement = SETTINGS_AGREEMENT_DISAGREE;
}

static void menuPower_HandleTouch()
{
	if (TouchFront_CheckIsReleased()) 
	{
		if (TouchFront_GetX() >= 185 && TouchFront_GetX() <= 295 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298){
			selection = 0;
		}
		else if (TouchFront_GetX() >= 345 && TouchFront_GetX() <= 455 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298){
			selection = 1;
		}
		else if (TouchFront_GetX() >= 505 && TouchFront_GetX() <= 615 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298){
			selection = 2;
		}
		else if (TouchFront_GetX() >= 660 && TouchFront_GetX() <= 770 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298){
			selection = 3;
		}
	}
	
	if (TouchFront_CheckIsPressed()) 
	{
		if (selection == 0 && (TouchFront_GetX() >= 185 && TouchFront_GetX() <= 295 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298)){
			shutdownDevice(); //BMK
		}
		else if (selection == 1 && (TouchFront_GetX() >= 345 && TouchFront_GetX() <= 455 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298)){
			rebootDevice(); //BMK
		}
		else if (selection == 2 && (TouchFront_GetX() >= 505 && TouchFront_GetX() <= 615 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298)){
			suspendDevice(); //BMK
		}
		else if (selection == 3 && (TouchFront_GetX() >= 660 && TouchFront_GetX() <= 770 && TouchFront_GetY() >= 188 && TouchFront_GetY() <= 298)){
			restartShell(); //BMK
		}
	}
}

static void menuSettings_HandleTouch()
{
	SettingsMenuOption *option = &settings_menu_entries[settings_menu.entry_sel].options[settings_menu.option_sel];
	
	if (TouchFront_CheckIsPressed()) 
	{
		if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 480 && TouchFront_GetY() >= 385 && TouchFront_GetY() <= 464){
			if (settings_menu.option_sel > 0) {
			  settings_menu.option_sel--;
			} else if (settings_menu.entry_sel > 0) {
			  settings_menu.entry_sel--;
			  settings_menu.option_sel = settings_menu_entries[settings_menu.entry_sel].n_options - 1;
			}
		}
		else if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 480 && TouchFront_GetY() >= 464 && TouchFront_GetY() <= 544){
			if (settings_menu.option_sel < settings_menu_entries[settings_menu.entry_sel].n_options - 1) {
			  settings_menu.option_sel++;
			} else if (settings_menu.entry_sel < n_settings_entries - 1) {
			  settings_menu.entry_sel++;
			  settings_menu.option_sel = 0;
			}
		}
		else if (TouchFront_GetX() >= 480 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 385 && TouchFront_GetY() <= 544){
			
			changed = 1;

			switch (option->type) {
			  case SETTINGS_OPTION_TYPE_BOOLEAN:
				if (option->value)
				  *(option->value) = !*(option->value);
				break;
			  
			  case SETTINGS_OPTION_TYPE_STRING:
				initImeDialog(language_container[option->name], option->string, option->size_string, SCE_IME_TYPE_EXTENDED_NUMBER, 0, 0);
				setDialogStep(DIALOG_STEP_SETTINGS_STRING);
				break;
				
			  case SETTINGS_OPTION_TYPE_CALLBACK:
				if (option->callback)
				  option->callback(&option);
				break;
				
			/////////////// BMK ////////////////
			  case SETTINGS_OPTION2_TYPE_STRING:
																	  
					loadPreview();						
						  
				break;
			////////////////////////////////////
				
			  case SETTINGS_OPTION_TYPE_OPTIONS:
			  {
				if (option->value) {
					if (*(option->value) < option->n_options - 1){
					  (*(option->value))++;
					}else{
					  *(option->value) = 0;
					}
				  }				
				break;
			  }
			}
			
			if (vitashell_config.backup_storage) {
				storage_location = SCE_TRUE;
				Options_SaveConfig(storage_location);
			}else{
				storage_location = SCE_FALSE;
				Options_SaveConfig(storage_location);
			}
			
		}
	}
}

void settingsMenuCtrl() {
  SettingsMenuOption *option = &settings_menu_entries[settings_menu.entry_sel].options[settings_menu.option_sel];
  TouchFront_Update();
  
  // Agreement
  if (agreement != SETTINGS_AGREEMENT_NONE) {
    agreement = SETTINGS_AGREEMENT_NONE;
  }

  if(value){
	  
	  if (pressed_pad[PAD_RIGHT])
			selection++;
		else if (pressed_pad[PAD_LEFT])
			selection--;

		if (selection > MAX_MENU_ITEMS)
			selection = 0;
		if (selection < 0)
			selection = MAX_MENU_ITEMS;

		menuPower_HandleTouch();
		
		if (pressed_pad[PAD_ENTER])
		{
			switch (selection)
			{
				case 0:
					shutdownDevice();
					break;
				case 1:
					rebootDevice();
					break;
				case 2:
					suspendDevice();
					break;
				case 3:
					restartShell();
					break;
			}
		}
		
		if (TouchFront_CheckIsPressed()) 
		{
			if (!(TouchFront_GetX() >= 34 && TouchFront_GetX() <= 926 && TouchFront_GetY() >= 158 && TouchFront_GetY() <= 386))
			closeSettingsMenu();
		}
	  
  }else{
  
  // Change options
  if (pressed_pad[PAD_ENTER] || pressed_pad[PAD_LEFT] || pressed_pad[PAD_RIGHT]) {
    changed = 1;

    switch (option->type) {
      case SETTINGS_OPTION_TYPE_BOOLEAN:
        if (option->value)
          *(option->value) = !*(option->value);
        break;
      
      case SETTINGS_OPTION_TYPE_STRING:
        initImeDialog(language_container[option->name], option->string, option->size_string, SCE_IME_TYPE_EXTENDED_NUMBER, 0, 0);
        setDialogStep(DIALOG_STEP_SETTINGS_STRING);
        break;
        
      case SETTINGS_OPTION_TYPE_CALLBACK:
        if (option->callback)
          option->callback(&option);
        break;
        
	/////////////// BMK ////////////////
	  case SETTINGS_OPTION2_TYPE_STRING:
									
			if (pressed_pad[PAD_ENTER]) {						  
			loadPreview();						
		}
				  
		break;
	////////////////////////////////////
		
      case SETTINGS_OPTION_TYPE_OPTIONS:
      {
        if (option->value) {
          if (pressed_pad[PAD_LEFT]) {
            if (*(option->value) > 0)
              (*(option->value))--;
            else
              *(option->value) = option->n_options - 1;
          } else if (pressed_pad[PAD_ENTER] || pressed_pad[PAD_RIGHT]) {
            if (*(option->value) < option->n_options - 1)
              (*(option->value))++;
            else
              *(option->value) = 0;
          }
        }
        
        break;
      }
    }
	
	if (vitashell_config.backup_storage) {
		storage_location = SCE_TRUE;
		Options_SaveConfig(storage_location);
	}else{
		storage_location = SCE_FALSE;
		Options_SaveConfig(storage_location);
	}
	
  }

	menuSettings_HandleTouch();
  
	  // Move
	  if (hold_pad[PAD_UP] || hold2_pad[PAD_LEFT_ANALOG_UP]) {
		if (settings_menu.option_sel > 0) {
		  settings_menu.option_sel--;
		} else if (settings_menu.entry_sel > 0) {
		  settings_menu.entry_sel--;
		  settings_menu.option_sel = settings_menu_entries[settings_menu.entry_sel].n_options - 1;
		}
	  } else if (hold_pad[PAD_DOWN] || hold2_pad[PAD_LEFT_ANALOG_DOWN]) {
		if (settings_menu.option_sel < settings_menu_entries[settings_menu.entry_sel].n_options - 1) {
		  settings_menu.option_sel++;
		} else if (settings_menu.entry_sel < n_settings_entries - 1) {
		  settings_menu.entry_sel++;
		  settings_menu.option_sel = 0;
		}
	  }else if (TouchFront_CheckIsPressed()) 
	  {
		if (!(TouchFront_GetX() >= 34 && TouchFront_GetX() <= 926 && TouchFront_GetY() >= 158 && TouchFront_GetY() <= 386) && !(TouchFront_GetX() >= 0 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 385 && TouchFront_GetY() <= 544))
			closeSettingsMenu();
	  }
	  
  }
  // Close
  if (pressed_pad[PAD_CANCEL]) {
    closeSettingsMenu();
  }
}
