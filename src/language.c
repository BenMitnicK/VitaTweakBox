/*
  VitaShell
  Copyright (C) 2015-2018, TheFloW

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
#include "language.h"

INCLUDE_EXTERN_RESOURCE(english_us_txt);

static char *lang[] = {
  "japanese",
  "english_us",
  "french",
  "spanish",
  "german",
  "italian",
  "dutch",
  "portuguese",
  "russian",
  "korean",
  "chinese_t",
  "chinese_s",
  "finnish",
  "swedish",
  "danish",
  "norwegian",
  "polish",
  "portuguese_br",
  "turkish"
};

char *language_container[LANGUAGE_CONTAINER_SIZE];

void freeLanguageContainer() {
  int i;
  for (i = 0; i < LANGUAGE_CONTAINER_SIZE; i++) {
    if (language_container[i]) {
      free(language_container[i]);
      language_container[i] = NULL;
    }
  }
}

void loadLanguage(int id) {
  freeLanguageContainer();

  #define LANGUAGE_ENTRY(name) { #name, CONFIG_TYPE_STRING, (void *)&language_container[name] }
  ConfigEntry language_entries[] = {
	////////// VitaShell //////////	  
    // General strings
    LANGUAGE_ENTRY(ERROR),
    LANGUAGE_ENTRY(OK),
    LANGUAGE_ENTRY(YES),
    LANGUAGE_ENTRY(NO),
    LANGUAGE_ENTRY(CANCEL),
    LANGUAGE_ENTRY(ON),
    LANGUAGE_ENTRY(OFF),
    LANGUAGE_ENTRY(FILE_),
    LANGUAGE_ENTRY(FOLDER),

    // Progress strings
    LANGUAGE_ENTRY(MOVING),
    LANGUAGE_ENTRY(COPYING),
    LANGUAGE_ENTRY(DELETING),
    LANGUAGE_ENTRY(EXPORTING),
    LANGUAGE_ENTRY(INSTALLING),
    LANGUAGE_ENTRY(DOWNLOADING),
    LANGUAGE_ENTRY(EXTRACTING),
    LANGUAGE_ENTRY(COMPRESSING),
    LANGUAGE_ENTRY(HASHING),
    LANGUAGE_ENTRY(REFRESHING),
    LANGUAGE_ENTRY(SENDING),
    LANGUAGE_ENTRY(RECEIVING),

    // Audio player strings
    LANGUAGE_ENTRY(TITLE),
    LANGUAGE_ENTRY(ALBUM),
    LANGUAGE_ENTRY(ARTIST),
    LANGUAGE_ENTRY(GENRE),
    LANGUAGE_ENTRY(YEAR),

    // Hex editor strings
    LANGUAGE_ENTRY(OFFSET),
    LANGUAGE_ENTRY(OPEN_HEX_EDITOR),

    // Text editor strings
    LANGUAGE_ENTRY(EDIT_LINE),
    LANGUAGE_ENTRY(ENTER_SEARCH_TERM),

    // Context menu strings
    LANGUAGE_ENTRY(REFRESH_LIVEAREA),
	LANGUAGE_ENTRY(CREDIT),
	LANGUAGE_ENTRY(CID),
    LANGUAGE_ENTRY(REFRESH_LICENSE_DB),
    LANGUAGE_ENTRY(MOUNT_UMA0),
    LANGUAGE_ENTRY(MOUNT_IMC0),
    LANGUAGE_ENTRY(MOUNT_XMC0),
    LANGUAGE_ENTRY(UMOUNT_UMA0),
    LANGUAGE_ENTRY(UMOUNT_IMC0),
    LANGUAGE_ENTRY(UMOUNT_XMC0),
    LANGUAGE_ENTRY(MOUNT_USB_UX0),
    LANGUAGE_ENTRY(UMOUNT_USB_UX0),
    LANGUAGE_ENTRY(MOUNT_GAMECARD_UX0),
    LANGUAGE_ENTRY(UMOUNT_GAMECARD_UX0),
    LANGUAGE_ENTRY(SORT_BY),
    LANGUAGE_ENTRY(BY_NAME),
    LANGUAGE_ENTRY(BY_SIZE),
    LANGUAGE_ENTRY(BY_DATE),
    LANGUAGE_ENTRY(MARK_ALL),
    LANGUAGE_ENTRY(UNMARK_ALL),
    LANGUAGE_ENTRY(MOVE),
    LANGUAGE_ENTRY(COPY),
    LANGUAGE_ENTRY(PASTE),
    LANGUAGE_ENTRY(DELETE),
    LANGUAGE_ENTRY(RENAME),
    LANGUAGE_ENTRY(NEW),
    LANGUAGE_ENTRY(NEW_FILE),
    LANGUAGE_ENTRY(NEW_FOLDER),
    LANGUAGE_ENTRY(PROPERTIES),
    LANGUAGE_ENTRY(SEND),
    LANGUAGE_ENTRY(RECEIVE),
    LANGUAGE_ENTRY(MORE),
    LANGUAGE_ENTRY(BOOKMARKS),
    LANGUAGE_ENTRY(ADHOC_TRANSFER),
    LANGUAGE_ENTRY(BOOKMARKS_SHOW),
    LANGUAGE_ENTRY(BOOKMARKS_NEW),
    LANGUAGE_ENTRY(RECENT_FILES_SHOW),
    LANGUAGE_ENTRY(COMPRESS),
    LANGUAGE_ENTRY(INSTALL_ALL),
    LANGUAGE_ENTRY(INSTALL_FOLDER),
    LANGUAGE_ENTRY(CALCULATE_SHA1),
    LANGUAGE_ENTRY(OPEN_DECRYPTED),
    LANGUAGE_ENTRY(EXPORT_MEDIA),
    LANGUAGE_ENTRY(CUT),
    LANGUAGE_ENTRY(INSERT_EMPTY_LINE),
    LANGUAGE_ENTRY(SEARCH),

    // File browser properties strings
    LANGUAGE_ENTRY(PROPERTY_NAME),
    LANGUAGE_ENTRY(PROPERTY_TYPE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE),
    LANGUAGE_ENTRY(PROPERTY_SIZE),
    LANGUAGE_ENTRY(PROPERTY_COMPRESSED_SIZE),
    LANGUAGE_ENTRY(PROPERTY_CONTAINS),
    LANGUAGE_ENTRY(PROPERTY_CONTAINS_FILES_FOLDERS),
    LANGUAGE_ENTRY(PROPERTY_CREATION_DATE),
    LANGUAGE_ENTRY(PROPERTY_MODFICATION_DATE),
    LANGUAGE_ENTRY(PROPERTY_TYPE_ARCHIVE),
    LANGUAGE_ENTRY(PROPERTY_TYPE_BMP),
    LANGUAGE_ENTRY(PROPERTY_TYPE_INI),
    LANGUAGE_ENTRY(PROPERTY_TYPE_JPEG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_MP3),
    LANGUAGE_ENTRY(PROPERTY_TYPE_OGG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_PNG),
    LANGUAGE_ENTRY(PROPERTY_TYPE_SFO),
    LANGUAGE_ENTRY(PROPERTY_TYPE_TXT),
    LANGUAGE_ENTRY(PROPERTY_TYPE_VPK),
    LANGUAGE_ENTRY(PROPERTY_TYPE_XML),
    LANGUAGE_ENTRY(PROPERTY_TYPE_FSELF),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_SAFE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_UNSAFE),
    LANGUAGE_ENTRY(PROPERTY_FSELF_MODE_SCE),

    // File browser strings
    LANGUAGE_ENTRY(REFRESHED),
    LANGUAGE_ENTRY(COPIED_FILE),
    LANGUAGE_ENTRY(COPIED_FOLDER),
    LANGUAGE_ENTRY(COPIED_FILES_FOLDERS),
    LANGUAGE_ENTRY(IMPORTED_LICENSES),

    // Dialog questions
    LANGUAGE_ENTRY(DELETE_FILE_QUESTION),
    LANGUAGE_ENTRY(DELETE_FOLDER_QUESTION),
    LANGUAGE_ENTRY(DELETE_FILES_FOLDERS_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FILE_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FOLDER_QUESTION),
    LANGUAGE_ENTRY(EXPORT_FILES_FOLDERS_QUESTION),
    LANGUAGE_ENTRY(EXPORT_NO_MEDIA),
    LANGUAGE_ENTRY(EXPORT_SONGS_INFO),
    LANGUAGE_ENTRY(EXPORT_VIDEOS_INFO),
    LANGUAGE_ENTRY(EXPORT_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_VIDEOS_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_VIDEOS_PICTURES_INFO),
    LANGUAGE_ENTRY(EXPORT_SONGS_VIDEOS_PICTURES_INFO),
    LANGUAGE_ENTRY(INSTALL_ALL_QUESTION),
    LANGUAGE_ENTRY(INSTALL_FOLDER_QUESTION),
    LANGUAGE_ENTRY(INSTALL_QUESTION),
    LANGUAGE_ENTRY(INSTALL_WARNING),
    LANGUAGE_ENTRY(INSTALL_BRICK_WARNING),
    LANGUAGE_ENTRY(HASH_FILE_QUESTION),
    LANGUAGE_ENTRY(SAVE_MODIFICATIONS),
    LANGUAGE_ENTRY(REFRESH_LIVEAREA_QUESTION),
    LANGUAGE_ENTRY(REFRESH_LICENSE_DB_QUESTION),

    // HENkaku settings strings
    LANGUAGE_ENTRY(HENKAKU_SETTINGS),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_PSN_SPOOFING),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_UNSAFE_HOMEBREW),
    LANGUAGE_ENTRY(HENKAKU_ENABLE_VERSION_SPOOFING),
    LANGUAGE_ENTRY(HENKAKU_SPOOFED_VERSION),
    LANGUAGE_ENTRY(HENKAKU_RESTORE_DEFAULT_SETTINGS),
    LANGUAGE_ENTRY(HENKAKU_RELOAD_CONFIG),
    LANGUAGE_ENTRY(HENKAKU_RESTORE_DEFAULT_MESSAGE),
    LANGUAGE_ENTRY(HENKAKU_RELOAD_CONFIG_MESSAGE),
    LANGUAGE_ENTRY(HENKAKU_UNSAFE_HOMEBREW_MESSAGE),

    // VitaShell settings
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_MAIN),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_LANGUAGE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_THEME),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USBDEVICE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_NO_AUTO_UPDATE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_WARNING_MESSAGE),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_RESTART_SHELL),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_POWER),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_REBOOT),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_POWEROFF),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_STANDBY),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_MEMORY_CARD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_GAME_CARD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_SD2VITA),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_USB_PSVSD),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON_USB),
    LANGUAGE_ENTRY(VITASHELL_SETTINGS_SELECT_BUTTON_FTP),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_DATABASE),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_DATABASE_UPDATE),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_DATABASE_REBUILD),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_DATABASE_EXPORT),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_DATABASE_IMPORT),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_MEM_INFO),
	LANGUAGE_ENTRY(VITASHELL_SETTINGS_BACKUP_STORAGE),
	
    // USB strings
    LANGUAGE_ENTRY(USB_CONNECTED),
    LANGUAGE_ENTRY(USB_UX0_MOUNTED),
    LANGUAGE_ENTRY(USB_UX0_UMOUNTED),
    LANGUAGE_ENTRY(GAMECARD_UX0_MOUNTED),
    LANGUAGE_ENTRY(GAMECARD_UX0_UMOUNTED),
    LANGUAGE_ENTRY(USB_NOT_CONNECTED),
    LANGUAGE_ENTRY(USB_CONNECTION_NOT_AVAILABLE),
    LANGUAGE_ENTRY(USB_WAIT_ATTACH),

    // QR strings
    LANGUAGE_ENTRY(QR_SCANNING),
    LANGUAGE_ENTRY(QR_OPEN_WEBSITE),
    LANGUAGE_ENTRY(QR_SHOW_CONTENTS),
    LANGUAGE_ENTRY(QR_CONFIRM_INSTALL),
    LANGUAGE_ENTRY(QR_CONFIRM_DOWNLOAD),
    
    // Adhoc strings
    LANGUAGE_ENTRY(ADHOC_RECEIVE_SEARCHING_PSVITA),
    LANGUAGE_ENTRY(ADHOC_SELECT_PSVITA),
    LANGUAGE_ENTRY(ADHOC_RECEIVE_QUESTION),
    LANGUAGE_ENTRY(ADHOC_CLIENT_DECLINED),
    
    // Others
    LANGUAGE_ENTRY(UMA0_MOUNTED),
    LANGUAGE_ENTRY(IMC0_MOUNTED),
    LANGUAGE_ENTRY(XMC0_MOUNTED),
    LANGUAGE_ENTRY(UMA0_UMOUNTED),
    LANGUAGE_ENTRY(IMC0_UMOUNTED),
    LANGUAGE_ENTRY(XMC0_UMOUNTED),
    LANGUAGE_ENTRY(SAFE_MODE),
    LANGUAGE_ENTRY(UNSAFE_MODE),
    LANGUAGE_ENTRY(PLEASE_WAIT),
    LANGUAGE_ENTRY(MEMORY_CARD_NOT_FOUND),
    LANGUAGE_ENTRY(GAME_CARD_NOT_FOUND),
    LANGUAGE_ENTRY(MICROSD_NOT_FOUND),
    LANGUAGE_ENTRY(NO_SPACE_ERROR),
    LANGUAGE_ENTRY(EXTENDED_PERMISSIONS_REQUIRED),
    LANGUAGE_ENTRY(WIFI_ERROR),
    LANGUAGE_ENTRY(FTP_SERVER),
    LANGUAGE_ENTRY(UPDATE_QUESTION),
    LANGUAGE_ENTRY(ARCHIVE_NAME),
    LANGUAGE_ENTRY(COMPRESSION_LEVEL),
    LANGUAGE_ENTRY(ENTER_PASSWORD),
	LANGUAGE_ENTRY(SAVECIDSUCCES),
    LANGUAGE_ENTRY(BOOKMARK_CREATED),
	
	////////// VTB //////////
	
	// Language Settings
	LANGUAGE_ENTRY(english_us),
	LANGUAGE_ENTRY(japanese),
	LANGUAGE_ENTRY(french),
	LANGUAGE_ENTRY(spanish),
	LANGUAGE_ENTRY(german),
	LANGUAGE_ENTRY(italian),
	LANGUAGE_ENTRY(dutch),
	LANGUAGE_ENTRY(portuguese),
	LANGUAGE_ENTRY(russian),
	LANGUAGE_ENTRY(korean),
	LANGUAGE_ENTRY(chinese_t),
	LANGUAGE_ENTRY(chinese_s),
	LANGUAGE_ENTRY(finnish),
	LANGUAGE_ENTRY(swedish),
	LANGUAGE_ENTRY(danish),
	LANGUAGE_ENTRY(norwegian),
	LANGUAGE_ENTRY(polish),
	LANGUAGE_ENTRY(portuguese_br),
	LANGUAGE_ENTRY(turkish),
		
	// VTB Menu
    LANGUAGE_ENTRY(VTB_VITAIDENT),
    LANGUAGE_ENTRY(VTB_VITABACKUP),
    LANGUAGE_ENTRY(VTB_FORECAST),
    LANGUAGE_ENTRY(VTB_DATABASE),
    LANGUAGE_ENTRY(VTB_OPTIONS),
    LANGUAGE_ENTRY(VTB_POWER),
    LANGUAGE_ENTRY(VTB_SHELL),
    LANGUAGE_ENTRY(VTB_CREDIT),
    LANGUAGE_ENTRY(VTB_FILE_TRANSFER),
    LANGUAGE_ENTRY(VTB_BOOKS),
		
	// Books
	LANGUAGE_ENTRY(BOOKS_NO_IMAGES),
		
	// DataBase
	LANGUAGE_ENTRY(DATABASEUPDATEQUESTION),
	LANGUAGE_ENTRY(DATABASEREBUILDQUESTION),
	LANGUAGE_ENTRY(DATABASEUPDATECONFIRMQUESTION),
	LANGUAGE_ENTRY(DATABASEREBUILDCONFIRMQUESTION),
	LANGUAGE_ENTRY(DATABASEREBUILDCONFIRMQUESTION2),
	LANGUAGE_ENTRY(DATABASELAYOUTAFTERREBUILD),
	LANGUAGE_ENTRY(IMPORT_ERROR),
	LANGUAGE_ENTRY(LIVEAREA_SETTINGS),
	LANGUAGE_ENTRY(EXPORT_ERROR),
	LANGUAGE_ENTRY(EXPORT_OK),
		
	// ForeCast
	LANGUAGE_ENTRY(FORECAST_KEYBOARD),
	LANGUAGE_ENTRY(FORECAST_HUMID),
	LANGUAGE_ENTRY(FORECAST_CLOUD),
	LANGUAGE_ENTRY(FORECAST_ATMOS),
	LANGUAGE_ENTRY(FORECAST_WIND),
	LANGUAGE_ENTRY(FORECASTERRORNETWORK),
    LANGUAGE_ENTRY(FORECASTERRORZIPCODE),
	
	// VitaBackup
    LANGUAGE_ENTRY(BACKUP_MENU),
    LANGUAGE_ENTRY(OPTIONS_MENU),
    LANGUAGE_ENTRY(RESTORE_MENU),
	// VitaBackup Restore
	LANGUAGE_ENTRY(SELECT_RESTORE_DATA),
	LANGUAGE_ENTRY(PRESS_START_RESTORE_PROCESS),
	LANGUAGE_ENTRY(RESTORE_PROGRESS),
	// VitaBackup Options
    LANGUAGE_ENTRY(OPTIONS),
    LANGUAGE_ENTRY(DESTINATIONS),
	// VitaBackup Menu
	LANGUAGE_ENTRY(SELECT_BACKUP_DATA),
	LANGUAGE_ENTRY(PRESS_START_BACKUP_PROCESS),
	LANGUAGE_ENTRY(BACKUP_PROGRESS),
	
	// Help
	LANGUAGE_ENTRY(HELP_BROWSER_CIRCLE),
	LANGUAGE_ENTRY(HELP_BROWSER_SQUARE),
	LANGUAGE_ENTRY(HELP_BROWSER_TRIANGLE),
	LANGUAGE_ENTRY(HELP_BROWSER_CROSS),
	LANGUAGE_ENTRY(HELP_BROWSER_SELECT),
	//LANGUAGE_ENTRY(HELP_BROWSER_START),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_CIRCLE),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_SQUARE),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_TRIANGLE),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_CROSS),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_PAD),
	LANGUAGE_ENTRY(HELP_TEXTEDITOR_LR),
	LANGUAGE_ENTRY(HELP_HEXEDITOR_CIRCLE),
	LANGUAGE_ENTRY(HELP_HEXEDITOR_SQUARE),
	LANGUAGE_ENTRY(HELP_HEXEDITOR_CROSS),
	LANGUAGE_ENTRY(HELP_HEXEDITOR_LR),
	LANGUAGE_ENTRY(HELP_PHOTOVIEWER_CIRCLE),
	LANGUAGE_ENTRY(HELP_PHOTOVIEWER_PAD),
	LANGUAGE_ENTRY(HELP_PHOTOVIEWER_LR),
	LANGUAGE_ENTRY(HELP_PHOTOVIEWER_CROSS_R),
	LANGUAGE_ENTRY(HELP_AUDIOPLAYER_CIRCLE),
	LANGUAGE_ENTRY(HELP_AUDIOPLAYER_TRIANGLE),
	LANGUAGE_ENTRY(HELP_AUDIOPLAYER_CROSS),
	LANGUAGE_ENTRY(HELP_AUDIOPLAYER_PAD),
	LANGUAGE_ENTRY(HELP_AUDIOPLAYER_LR),
	LANGUAGE_ENTRY(HELP_BOOK_TRIANGLE),
	LANGUAGE_ENTRY(HELP_BOOK_PAD),
	LANGUAGE_ENTRY(HELP_BOOK_LR),
	LANGUAGE_ENTRY(HELP_BOOK_CROSS_R),
	
	// Book
    LANGUAGE_ENTRY(NO_BOOKS_FOUND),
    LANGUAGE_ENTRY(NO_IMAGES_FOUND)
  };

  // Load default config file
  readConfigBuffer(&_binary_resources_english_us_txt_start, (int)&_binary_resources_english_us_txt_size,
                   language_entries, sizeof(language_entries) / sizeof(ConfigEntry));

  // Load custom config file
	if (use_custom_config) {
		if (id >= 0 && id < (sizeof(lang) / sizeof(char *))) {
			char path[MAX_PATH_LENGTH];
			/*snprintf(path, MAX_PATH_LENGTH, "ux0:VitaShell/language/%s.txt", lang[id]);
			readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));*/
			switch (vitashell_config.select_lang) {
				case 0:
					sprintf(path, "ux0:VitaTweakBox/language/english_us.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				
				case 1:
					sprintf(path, "ux0:VitaTweakBox/language/japanese.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 2:
					sprintf(path, "ux0:VitaTweakBox/language/french.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 3:
					sprintf(path, "ux0:VitaTweakBox/language/spanish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 4:
					sprintf(path, "ux0:VitaTweakBox/language/german.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				
				case 5:
					sprintf(path, "ux0:VitaTweakBox/language/italian.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 6:
					sprintf(path, "ux0:VitaTweakBox/language/dutch.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 7:
					sprintf(path, "ux0:VitaTweakBox/language/portuguese.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 8:
					sprintf(path, "ux0:VitaTweakBox/language/russian.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				
				case 9:
					sprintf(path, "ux0:VitaTweakBox/language/korean.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 10:
					sprintf(path, "ux0:VitaTweakBox/language/chinese_t.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 11:
					sprintf(path, "ux0:VitaTweakBox/language/chinese_s.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 12:
					sprintf(path, "ux0:VitaTweakBox/language/finnish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				
				case 13:
					sprintf(path, "ux0:VitaTweakBox/language/swedish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 14:
					sprintf(path, "ux0:VitaTweakBox/language/danish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 15:
					sprintf(path, "ux0:VitaTweakBox/language/norwegian.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 16:
					sprintf(path, "ux0:VitaTweakBox/language/polish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				
				case 17:
					sprintf(path, "ux0:VitaTweakBox/language/portuguese_br.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
					
				case 18:
					sprintf(path, "ux0:VitaTweakBox/language/turkish.txt");
					readConfig(path, language_entries, sizeof(language_entries) / sizeof(ConfigEntry));
					break;
				}
		}
	}
}
