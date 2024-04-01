/*
  VitaShell
  Copyright (C) 2015-2018, TheFloW And BenMitnicK

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
#include "main_context.h"
#include "browser.h"
#include "init.h"
#include "io_process.h"
#include "refresh.h"
#include "makezip.h"
#include "package_installer.h"
#include "context_menu.h"
#include "archive.h"
#include "photo.h"
#include "audioplayer.h"
#include "file.h"
#include "text.h"
#include "hex.h"
#include "settings.h"
#include "database.h" //BMK
#include "main_vtb.h" //BMK
#include "help.h" //BMK
#include "vitaident/vitaident.h" //BMK
#include "vitaforecast/forecast.h" //BMK
#include "vitabackup/vitabackup.h" //BMK
#include "book/book.h" //BMK
#include "book/book_images.h" //BMK
//#include "atrac/bgm.h" //BMK
#include "credits.h" //BMK
#include "adhoc_dialog.h"
#include "property_dialog.h"
#include "message_dialog.h"
#include "netcheck_dialog.h"
#include "ime_dialog.h"
#include "theme.h"
#include "language.h"
#include "utils.h"
#include "touch.h"
#include "sfo.h"
#include "coredump.h"
#include "usb.h"
#include "qr.h"

#define MAX_ITEMS   9

static int selection = 0;

static void file_Transfer(){
	
	if (vitashell_config.select_button == SELECT_BUTTON_MODE_USB &&
        sceKernelGetModel() == SCE_KERNEL_MODEL_VITA) {
      if (isSafeMode()) {
        infoDialog(language_container[EXTENDED_PERMISSIONS_REQUIRED]);
      } else {
        SceUdcdDeviceState state;
        sceUdcdGetDeviceState(&state);

        if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED) {
          initUsb();
        } else {
          initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL,
                            language_container[USB_NOT_CONNECTED]);
          setDialogStep(DIALOG_STEP_USB_WAIT);
        }
      }
    } else if (vitashell_config.select_button == SELECT_BUTTON_MODE_FTP ||
               sceKernelGetModel() == SCE_KERNEL_MODEL_VITATV) {
      // Init FTP
      if (!ftpvita_is_initialized()) {
        int res = ftpvita_init(vita_ip, &vita_port);
        if (res < 0) {
          initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL, language_container[PLEASE_WAIT]);
          setDialogStep(DIALOG_STEP_FTP_WAIT);
        } else {
          initFtp();
        }

        // Lock power timers
        powerLock();
      }

      // Dialog
      if (ftpvita_is_initialized()) {
        initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL, language_container[FTP_SERVER],
                          vita_ip, vita_port);
        setDialogStep(DIALOG_STEP_FTP);
      }
    }
	
}

static void menuVTB_HandleTouch()
{
	if (TouchFront_CheckIsReleased()) 
	{
		if (TouchFront_GetX() >= 85 && TouchFront_GetX() <= 195 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224){
			selection = 0;
		}
		else if (TouchFront_GetX() >= 255 && TouchFront_GetX() <= 365 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224){
			selection = 1;
		}
		else if (TouchFront_GetX() >= 425 && TouchFront_GetX() <= 535 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224){
			selection = 2;
		}
		else if (TouchFront_GetX() >= 595 && TouchFront_GetX() <= 705 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224){
			selection = 3;
		}
		else if (TouchFront_GetX() >= 765 && TouchFront_GetX() <= 875 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224){
			selection = 4;
		}
		else if (TouchFront_GetX() >= 85 && TouchFront_GetX() <= 195 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394){
			selection = 5;
		}
		else if (TouchFront_GetX() >= 255 && TouchFront_GetX() <= 365 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394){
			selection = 6;
		}
		else if (TouchFront_GetX() >= 425 && TouchFront_GetX() <= 535 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394){
			selection = 7;
		}
		else if (TouchFront_GetX() >= 595 && TouchFront_GetX() <= 705 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394){
			selection = 8;
		}
		else if (TouchFront_GetX() >= 765 && TouchFront_GetX() <= 875 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394){
			selection = 9;
		}
	}
	
	if (TouchFront_CheckIsPressed()) 
	{
		if (selection == 0 && (TouchFront_GetX() >= 85 && TouchFront_GetX() <= 195 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224)){
			openVitaidentMenu(); //BMK
		}
		else if (selection == 1 && (TouchFront_GetX() >= 255 && TouchFront_GetX() <= 365 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224)){
			openVitabackupMenu(); //BMK
		}
		else if (selection == 2 && (TouchFront_GetX() >= 425 && TouchFront_GetX() <= 535 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224)){
			openForeCastMenu(); //BMK
		}
		else if (selection == 3 && (TouchFront_GetX() >= 595 && TouchFront_GetX() <= 705 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224)){
			openDataBaseMenu(); //BMK
		}
		else if (selection == 4 && (TouchFront_GetX() >= 765 && TouchFront_GetX() <= 875 && TouchFront_GetY() >= 114 && TouchFront_GetY() <= 224)){
			value = 0;
			openSettingsMenu();
		}
		else if (selection == 5 && (TouchFront_GetX() >= 85 && TouchFront_GetX() <= 195 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394)){
			value = 1;
			openSettingsMenu();
		}
		else if (selection == 6 && (TouchFront_GetX() >= 255 && TouchFront_GetX() <= 365 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394)){
			openBrowserMenu(); //BMK
		}
		else if (selection == 7 && (TouchFront_GetX() >= 425 && TouchFront_GetX() <= 535 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394)){
			openCreditsMenu(); //BMK
		}
		else if (selection == 8 && (TouchFront_GetX() >= 595 && TouchFront_GetX() <= 705 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394)){
			file_Transfer(); //BMK
		}
		else if (selection == 9 && (TouchFront_GetX() >= 765 && TouchFront_GetX() <= 875 && TouchFront_GetY() >= 284 && TouchFront_GetY() <= 394)){
			openBookMenu(); //BMK
		}
	}
	
	//return selection;
}

static int AppMenuCtrl() {
	int refresh = 0;
	TouchFront_Update();
	
		if(pressed_pad[PAD_RIGHT] || pressed_pad[PAD_LEFT_ANALOG_RIGHT] || hold_pad[PAD_RIGHT] || hold_pad[PAD_LEFT_ANALOG_RIGHT]){
			selection++; //Moves the selector down
		}else if(pressed_pad[PAD_LEFT] || pressed_pad[PAD_LEFT_ANALOG_LEFT] || hold_pad[PAD_LEFT] || hold_pad[PAD_LEFT_ANALOG_LEFT]){
			selection--; //Moves the selector up
		}else if(pressed_pad[PAD_UP] || pressed_pad[PAD_LEFT_ANALOG_UP]){
			if((selection-5) < 0){
				selection += 5;		
			}
			else {
				selection -= 5;
			}
		}else if(pressed_pad[PAD_DOWN] || pressed_pad[PAD_LEFT_ANALOG_DOWN]){
			if((selection+5) > 9){
				selection -= 5;		
			}
			else {
				selection += 5;
			}
		}else if (pressed_pad[PAD_ENTER]){
			
			switch (selection)
			{
				case 0:
					openVitaidentMenu(); //BMK
					break;
				case 1:
					openVitabackupMenu(); //BMK
					break;
				case 2:
					openForeCastMenu(); //BMK
					break;
				case 3:
					openDataBaseMenu(); //BMK
					break;
				case 4:
					value = 0;
					openSettingsMenu();
					break;
				case 5:
					value = 1;
					openSettingsMenu();
					break;
				case 6:
					openBrowserMenu(); //BMK
					break;
				case 7:
					openCreditsMenu(); //BMK
					break;
				case 8:
					file_Transfer(); //BMK
					break;
				case 9:
					//infoDialog("Coming Soon :)"); //BMK
					openBookMenu(); //BMK
					break;
			}
			
		}
		
		//selection = Menu_HandleTouch(selection);
		menuVTB_HandleTouch();
		
        if (selection > MAX_ITEMS) 
			selection = 0; //Sets the selection to the first
        if (selection < 0) 
			selection = MAX_ITEMS; //Sets the selection back to last
		
	return refresh;
}

void menuVTBMain()
{
		uint32_t vtbmenu_eC = epileptik();
		float x;

		vita2d_draw_texture(ico_appmenu_vitaident, 80, 109);
		vita2d_draw_texture(ico_appmenu_vitabackup, 250, 109);
		vita2d_draw_texture(ico_appmenu_forecast, 420, 109);		
		vita2d_draw_texture(ico_appmenu_database, 590, 109);
		vita2d_draw_texture(ico_appmenu_options, 760, 109);
		vita2d_draw_texture(ico_appmenu_power, 80, 279);
		vita2d_draw_texture(ico_appmenu_shell, 250, 279);
		vita2d_draw_texture(ico_appmenu_credit, 420, 279);
		vita2d_draw_texture(ico_appmenu_file_transfer, 590, 279);
		vita2d_draw_texture(ico_appmenu_books, 760, 279);
		
		vita2d_draw_fill_circle(140, 169, 55, selection == 0? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(310, 169, 55, selection == 1? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(480, 169, 55, selection == 2? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(650, 169, 55, selection == 3? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(820, 169, 55, selection == 4? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(140, 339, 55, selection == 5? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(310, 339, 55, selection == 6? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(480, 339, 55, selection == 7? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(650, 339, 55, selection == 8? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		vita2d_draw_fill_circle(820, 339, 55, selection == 9? RGBA8(VTB_MENU_R, VTB_MENU_G, VTB_MENU_B, vtbmenu_eC) : RGBA8(0, 0, 0, 0));
		
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_VITAIDENT]);
		pgf_draw_text(ALIGN_CENTER(120, x)+80, 244, VTB_MENU_VITAIDENT_COLOR, language_container[VTB_VITAIDENT]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_VITABACKUP]);
		pgf_draw_text(ALIGN_CENTER(120, x)+250, 244, VTB_MENU_VITABACKUP_COLOR, language_container[VTB_VITABACKUP]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_FORECAST]);
		pgf_draw_text(ALIGN_CENTER(120, x)+420, 244, VTB_MENU_FORECAST_COLOR, language_container[VTB_FORECAST]);		
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_DATABASE]);
		pgf_draw_text(ALIGN_CENTER(120, x)+590, 244, VTB_MENU_DATABASE_COLOR, language_container[VTB_DATABASE]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_OPTIONS]);
		pgf_draw_text(ALIGN_CENTER(120, x)+760, 244, VTB_MENU_OPTIONS_COLOR, language_container[VTB_OPTIONS]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_POWER]);
		pgf_draw_text(ALIGN_CENTER(120, x)+80, 414, VTB_MENU_POWER_COLOR, language_container[VTB_POWER]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_SHELL]);
		pgf_draw_text(ALIGN_CENTER(120, x)+250, 414, VTB_MENU_SHELL_COLOR, language_container[VTB_SHELL]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_CREDIT]);
		pgf_draw_text(ALIGN_CENTER(120, x)+420, 414, VTB_MENU_FILE_TRANSFER_COLOR, language_container[VTB_CREDIT]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_FILE_TRANSFER]);
		pgf_draw_text(ALIGN_CENTER(120, x)+590, 414, VTB_MENU_CREDIT_COLOR, language_container[VTB_FILE_TRANSFER]);
		x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[VTB_BOOKS]);
		pgf_draw_text(ALIGN_CENTER(120, x)+760, 414, VTB_MENU_BOOKS_COLOR, language_container[VTB_BOOKS]);

}

void loadSplashScreen(){
	
	vita2d_start_drawing();
    vita2d_clear_screen();
    vita2d_draw_texture(splashScreen, 0, 0);
    vita2d_end_drawing();
    vita2d_swap_buffers();
    sceDisplayWaitVblankStart();
    sceKernelDelayThread(2 * 1000 * 1000);
	
	int alpha = 255;
    for (; alpha > 3; alpha-=3) {
        vita2d_start_drawing();
        vita2d_clear_screen();
        vita2d_draw_texture_tint(splashScreen, 0, 0, RGBA8(255, 255, 255, alpha));
        vita2d_end_drawing();
        vita2d_swap_buffers();
        sceDisplayWaitVblankStart();
    }
}

int vtbMain() {

  // Init settings menu
  initSettingsMenu();
  
  // Init database menu BMK
  initDataBaseMenu();	
  // Init vitaident menu BMK
  initVitaidentMenu();	
  // Init ForeCast menu BMK
  initForeCastMenu();  
  // Init VitaBackup BMK
  initVitabackupMenu();
  // Init VitaBackup menu BMK
  initVitamenubackupMenu();
  // Init VitaRestore menu BMK
  initVitarestoreMenu();
  // Init AppMenu menu BMK
  initBrowserMenu();  
  // Init credits menu BMK
  initCreditsMenu();
  // Init help menu BMK
  initHelpMenu();
  // Init help menu BMK
  initBookMenu();
  // init bookarray
  initBookImagesArray();

  loadSplashScreen();
  
  while (1) {
    readPad();

    int refresh = REFRESH_MODE_NONE;
	int refresh2 = REFRESH_MODE_NONE;

    // Control
    if (getDialogStep() != DIALOG_STEP_NONE) {
      refresh = dialogSteps();
      // scroll_count = 0;
    } else if (getSettingsMenuStatus() != SETTINGS_MENU_CLOSED) {
      settingsMenuCtrl();
    } else if (getDataBaseMenuStatus() != DATABASE_MENU_CLOSED) {
	  databaseMenuCtrl(); //BMK
	} else if (getVitaidentMenuStatus() != VITAIDENT_MENU_CLOSED) {
	  VitaidentMenuCtrl(); //BMK
	} else if (getForeCastMenuStatus() != FORECAST_MENU_CLOSED) {
	  ForeCastMenuCtrl(); //BMK
	} else if (getVitabackupMenuStatus() != VITABACKUP_MENU_CLOSED) {
	  VitabackupMenuCtrl(); //BMK
	} else if (getVitamenubackupMenuStatus() != VITAMENUBACKUP_MENU_CLOSED) {
	  VitamenubackupMenuCtrl(); //BMK
	} else if (getVitarestoreMenuStatus() != VITARESTORE_MENU_CLOSED) {
	  VitarestoreMenuCtrl(); //BMK
	} else if (getBrowserMenuStatus() != BROWSER_MENU_CLOSED) {
	  BrowserMenuCtrl(); //BMK
	} else if (getCreditsMenuStatus() != CREDITS_MENU_CLOSED) {
	  CreditsMenuCtrl(); //BMK
	} else if (getHelpMenuStatus() != HELP_MENU_CLOSED) {
	  HelpMenuCtrl(); //BMK
	} else if (getBookMenuStatus() != BOOK_MENU_CLOSED) {
	  BookMenuCtrl(); //BMK
	}else {
      refresh = AppMenuCtrl();
    }

	// Receive system event
    SceAppMgrSystemEvent event;
    sceAppMgrReceiveSystemEvent(&event);

    // Refresh on app resume
    if (event.systemEvent == SCE_APPMGR_SYSTEMEVENT_ON_RESUME) {
      sceShellUtilLock(SCE_SHELL_UTIL_LOCK_TYPE_USB_CONNECTION);
      pfsUmount(); // umount game data at resume
      refresh = REFRESH_MODE_NORMAL;
	  refresh2 = REFRESH_MODE_NORMAL;
    }
    if (refresh != REFRESH_MODE_NONE) {
      // Refresh lists
      refreshFileList();
      refreshMarkList();
      refreshCopyList();

      // Focus
      if (refresh2 == REFRESH_MODE_SETFOCUS)
        setFocusOnFilename(focus_name);
    }
	
    // Start drawing
    startDrawing(vtb_main_image);

	// VTB Menu Draw
    menuVTBMain();
    
    // Draw
    drawSettingsMenu();

	// Draw BMK
	drawDataBaseMenu();
	drawVitaidentMenu();
	drawForeCastMenu();
	drawVitabackupMenu();
	drawVitamenubackupMenu();
	drawVitarestoreMenu();
	drawBrowserMenu();
	drawCreditsMenu();
	drawHelpMenu();
	drawBookMenu();

    // End drawing
    endDrawing();
  }

  // Empty lists
  fileListEmpty(&copy_list);
  fileListEmpty(&mark_list);
  fileListEmpty(&file_list);
 
  return 0;
}
