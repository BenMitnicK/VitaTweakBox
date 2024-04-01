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

#ifndef __THEME_H__
#define __THEME_H__

/////////////// BMK ////////////////
#define MAX_WALLPAPERS 20

// THEME POSITION & SIZE
extern int NAME_X_POSITION;
extern int NAME_Y_POSITION;
extern int NAME_SIZE;
extern int NAME_CENTER_DIM;
extern int PREVIEW_X_POSITION;
extern int PREVIEW_Y_POSITION;
extern int SCALE_X_POSITION;
extern int SCALE_Y_POSITION;
extern int FILTER_R_COLOR;
extern int FILTER_G_COLOR;
extern int FILTER_B_COLOR;
extern int FILTER_A_COLOR;
extern int FILTER_RW;
extern int FILTER_RH;
extern int FILTER_ACTIVE;
// VTB Menu Colors (epileptik)
extern int VTB_MENU_R;
extern int VTB_MENU_G;
extern int VTB_MENU_B;
// Vitaident Menu Colors (epileptik)
extern int VITAIDENT_MENU_R;
extern int VITAIDENT_MENU_G;
extern int VITAIDENT_MENU_B;
// Power Menu Colors (epileptik)
extern int POWER_MENU_R;
extern int POWER_MENU_G;
extern int POWER_MENU_B;
// Vitabackup Menu Colors (epileptik)
extern int VITABACKUP_MENU_R;
extern int VITABACKUP_MENU_G;
extern int VITABACKUP_MENU_B;
// Help Menu POSITION
// HelpBrowser
extern int HELP_BROWSER_CIRCLE_X;
extern int HELP_BROWSER_CIRCLE_Y;
extern int HELP_BROWSER_CROSS_X;
extern int HELP_BROWSER_CROSS_Y;
extern int HELP_BROWSER_SQUARE_X;
extern int HELP_BROWSER_SQUARE_Y;
extern int HELP_BROWSER_TRIANGLE_X;
extern int HELP_BROWSER_TRIANGLE_Y;
extern int HELP_BROWSER_SELECT_X;
extern int HELP_BROWSER_SELECT_Y;
//extern int HELP_BROWSER_START_X;
//extern int HELP_BROWSER_START_Y;
extern int HELP_BROWSER_CIRCLE_TEXT_X;
extern int HELP_BROWSER_CIRCLE_TEXT_Y;
extern int HELP_BROWSER_SQUARE_TEXT_X;
extern int HELP_BROWSER_SQUARE_TEXT_Y;
extern int HELP_BROWSER_TRIANGLE_TEXT_X;
extern int HELP_BROWSER_TRIANGLE_TEXT_Y;
extern int HELP_BROWSER_CROSS_TEXT_X;
extern int HELP_BROWSER_CROSS_TEXT_Y;
extern int HELP_BROWSER_SELECT_TEXT_X;
extern int HELP_BROWSER_SELECT_TEXT_Y;
//extern int HELP_BROWSER_START_TEXT_X;
//extern int HELP_BROWSER_START_TEXT_Y;
// HelpTextEditor
extern int HELP_TEXTEDITOR_CIRCLE_X;
extern int HELP_TEXTEDITOR_CIRCLE_Y;
extern int HELP_TEXTEDITOR_CROSS_X;
extern int HELP_TEXTEDITOR_CROSS_Y;
extern int HELP_TEXTEDITOR_SQUARE_X;
extern int HELP_TEXTEDITOR_SQUARE_Y;
extern int HELP_TEXTEDITOR_TRIANGLE_X;
extern int HELP_TEXTEDITOR_TRIANGLE_Y;
extern int HELP_TEXTEDITOR_PAD_X;
extern int HELP_TEXTEDITOR_PAD_Y;
extern int HELP_TEXTEDITOR_LR_X;
extern int HELP_TEXTEDITOR_LR_Y;
extern int HELP_TEXTEDITOR_CIRCLE_TEXT_X;
extern int HELP_TEXTEDITOR_CIRCLE_TEXT_Y;
extern int HELP_TEXTEDITOR_SQUARE_TEXT_X;
extern int HELP_TEXTEDITOR_SQUARE_TEXT_Y;
extern int HELP_TEXTEDITOR_TRIANGLE_TEXT_X;
extern int HELP_TEXTEDITOR_TRIANGLE_TEXT_Y;
extern int HELP_TEXTEDITOR_CROSS_TEXT_X;
extern int HELP_TEXTEDITOR_CROSS_TEXT_Y;
extern int HELP_TEXTEDITOR_PAD_TEXT_X;
extern int HELP_TEXTEDITOR_PAD_TEXT_Y;
extern int HELP_TEXTEDITOR_LR_TEXT_X;
extern int HELP_TEXTEDITOR_LR_TEXT_Y;
// HelpHexEditor
extern int HELP_HEXEDITOR_CIRCLE_X;
extern int HELP_HEXEDITOR_CIRCLE_Y;
extern int HELP_HEXEDITOR_CROSS_X;
extern int HELP_HEXEDITOR_CROSS_Y;
extern int HELP_HEXEDITOR_SQUARE_X;
extern int HELP_HEXEDITOR_SQUARE_Y;
extern int HELP_HEXEDITOR_LR_X;
extern int HELP_HEXEDITOR_LR_Y;
extern int HELP_HEXEDITOR_CIRCLE_TEXT_X;
extern int HELP_HEXEDITOR_CIRCLE_TEXT_Y;
extern int HELP_HEXEDITOR_SQUARE_TEXT_X;
extern int HELP_HEXEDITOR_SQUARE_TEXT_Y;
extern int HELP_HEXEDITOR_CROSS_TEXT_X;
extern int HELP_HEXEDITOR_CROSS_TEXT_Y;
extern int HELP_HEXEDITOR_LR_TEXT_X;
extern int HELP_HEXEDITOR_LR_TEXT_Y;
// HelpPhotoViewer
extern int HELP_PHOTOVIEWER_CIRCLE_X;
extern int HELP_PHOTOVIEWER_CIRCLE_Y;
extern int HELP_PHOTOVIEWER_PAD_X;
extern int HELP_PHOTOVIEWER_PAD_Y;
extern int HELP_PHOTOVIEWER_LR_X;
extern int HELP_PHOTOVIEWER_LR_Y;
extern int HELP_PHOTOVIEWER_CROSS_X;
extern int HELP_PHOTOVIEWER_CROSS_Y;
extern int HELP_PHOTOVIEWER_R_ANALOG_X;
extern int HELP_PHOTOVIEWER_R_ANALOG_Y;
extern int HELP_PHOTOVIEWER_CIRCLE_TEXT_X;
extern int HELP_PHOTOVIEWER_CIRCLE_TEXT_Y;
extern int HELP_PHOTOVIEWER_PAD_TEXT_X;
extern int HELP_PHOTOVIEWER_PAD_TEXT_Y;
extern int HELP_PHOTOVIEWER_LR_TEXT_X;
extern int HELP_PHOTOVIEWER_LR_TEXT_Y;
extern int HELP_PHOTOVIEWER_CROSS_TEXT_X;
extern int HELP_PHOTOVIEWER_CROSS_TEXT_Y;
extern int HELP_PHOTOVIEWER_R_ANALOG_TEXT_X;
extern int HELP_PHOTOVIEWER_R_ANALOG_TEXT_Y;
// HelpAudioPlayer
extern int HELP_AUDIOPLAYER_CIRCLE_X;
extern int HELP_AUDIOPLAYER_CIRCLE_Y;
extern int HELP_AUDIOPLAYER_CROSS_X;
extern int HELP_AUDIOPLAYER_CROSS_Y;
extern int HELP_AUDIOPLAYER_TRIANGLE_X;
extern int HELP_AUDIOPLAYER_TRIANGLE_Y;
extern int HELP_AUDIOPLAYER_PAD_X;
extern int HELP_AUDIOPLAYER_PAD_Y;
extern int HELP_AUDIOPLAYER_LR_X;
extern int HELP_AUDIOPLAYER_LR_Y;
extern int HELP_AUDIOPLAYER_CIRCLE_TEXT_X;
extern int HELP_AUDIOPLAYER_CIRCLE_TEXT_Y;
extern int HELP_AUDIOPLAYER_TRIANGLE_TEXT_X;
extern int HELP_AUDIOPLAYER_TRIANGLE_TEXT_Y;
extern int HELP_AUDIOPLAYER_CROSS_TEXT_X;
extern int HELP_AUDIOPLAYER_CROSS_TEXT_Y;
extern int HELP_AUDIOPLAYER_PAD_TEXT_X;
extern int HELP_AUDIOPLAYER_PAD_TEXT_Y;
extern int HELP_AUDIOPLAYER_LR_TEXT_X;
extern int HELP_AUDIOPLAYER_LR_TEXT_Y;
// HelpBookViewer
extern int HELP_BOOK_TRIANGLE_X;
extern int HELP_BOOK_TRIANGLE_Y;
extern int HELP_BOOK_PAD_X;
extern int HELP_BOOK_PAD_Y;
extern int HELP_BOOK_LR_X;
extern int HELP_BOOK_LR_Y;
extern int HELP_BOOK_CROSS_X;
extern int HELP_BOOK_CROSS_Y;
extern int HELP_BOOK_R_ANALOG_X;
extern int HELP_BOOK_R_ANALOG_Y;
extern int HELP_BOOK_TRIANGLE_TEXT_X;
extern int HELP_BOOK_TRIANGLE_TEXT_Y;
extern int HELP_BOOK_PAD_TEXT_X;
extern int HELP_BOOK_PAD_TEXT_Y;
extern int HELP_BOOK_LR_TEXT_X;
extern int HELP_BOOK_LR_TEXT_Y;
extern int HELP_BOOK_CROSS_TEXT_X;
extern int HELP_BOOK_CROSS_TEXT_Y;
extern int HELP_BOOK_R_ANALOG_TEXT_X;
extern int HELP_BOOK_R_ANALOG_TEXT_Y;
////////////////////////////////////

/////////////// BMK ////////////////
// VTB Menu colors
extern int VTB_BACKGROUND_COLOR;
extern int VTB_MENU_VITAIDENT_COLOR;
extern int VTB_MENU_VITABACKUP_COLOR;
extern int VTB_MENU_FORECAST_COLOR;
extern int VTB_MENU_DATABASE_COLOR;
extern int VTB_MENU_OPTIONS_COLOR;
extern int VTB_MENU_POWER_COLOR;
extern int VTB_MENU_SHELL_COLOR;
extern int VTB_MENU_FILE_TRANSFER_COLOR;
extern int VTB_MENU_CREDIT_COLOR;
extern int VTB_MENU_BOOKS_COLOR;

// Book colors
extern int BOOK_MENU_COLOR;

// HelpMenu colors
extern int HELP_MENU_COLOR;
extern int HELP_MENU_ITEM_COLOR;

// PowerMenu colors
extern int POWERMENU_REBOOT_COLOR;
extern int POWERMENU_SHUTDOWN_COLOR;
extern int POWERMENU_STANDBY_COLOR;
extern int POWERMENU_VTB_REBOOT_COLOR;

// DataBase colors
extern int DATABASE_MENU_COLOR;
extern int DATABASE_MENU_FOCUS_COLOR;
extern int DATABASE_MENU_TITLE_COLOR;
extern int DATABASE_MENU_ITEM_COLOR;
extern int DATABASE_MENU_OPTION_COLOR;

// Books colors
extern int BOOK_IMAGES_MENU_COLOR;
extern int BOOK_NO_IMAGES_COLOR;

// ThemeManager colors
extern int THEMEMANAGER_ITEM_COLOR;

// Vitaident colors
extern int VITAIDENT_MENU_COLOR;
extern int VITAIDENT_TITLE_KERNEL_COLOR;
extern int VITAIDENT_TITLE_SYSTEM_COLOR;
extern int VITAIDENT_TITLE_BATTERY_COLOR;
extern int VITAIDENT_TITLE_STORAGE_COLOR;
extern int VITAIDENT_TITLE_WIFI_COLOR;
extern int VITAIDENT_TITLE_MISC_COLOR;
extern int VITAIDENT_TITLE_CONFIG_COLOR;
extern int VITAIDENT_TITLE_PSN_COLOR;
extern int VITAIDENT_KERNEL_NAME_COLOR;
extern int VITAIDENT_KERNEL_ITEM_COLOR;
extern int VITAIDENT_SYSTEM_NAME_COLOR;
extern int VITAIDENT_SYSTEM_ITEM_COLOR;
extern int VITAIDENT_BATTERY_NAME_COLOR;
extern int VITAIDENT_BATTERY_ITEM_COLOR;
extern int VITAIDENT_STORAGE_NAME_COLOR;
extern int VITAIDENT_STORAGE_ITEM_COLOR;
extern int VITAIDENT_STORAGE_DEVICE_COLOR;
extern int VITAIDENT_STORAGE_BORDER_COLOR;
extern int VITAIDENT_STORAGE_INSIDE_COLOR;
extern int VITAIDENT_STORAGE_BAR_COLOR;
extern int VITAIDENT_WIFI_NAME_COLOR;
extern int VITAIDENT_WIFI_ITEM_COLOR;
extern int VITAIDENT_WIFI_PROFILE_COLOR;
extern int VITAIDENT_MISC_NAME_COLOR;
extern int VITAIDENT_MISC_ITEM_COLOR;
extern int VITAIDENT_WIFI_BORDER_COLOR;
extern int VITAIDENT_WIFI_INSIDE_COLOR;
extern int VITAIDENT_CONFIG_NAME_COLOR;
extern int VITAIDENT_CONFIG_ITEM_COLOR;
extern int VITAIDENT_PSN_NAME_COLOR;
extern int VITAIDENT_PSN_ITEM_COLOR;

// VitaBackup colors
extern int VITABACKUP_MENU_COLOR;
extern int VITABACKUP_TEXT_COLOR;
// Restore
extern int RESTORE_MENU_COLOR;
extern int VITABACKUP_RESTORE_TIITLE_TEXT_COLOR;
extern int VITABACKUP_RESTORE_TEXT_COLOR;
extern int VITABACKUP_RESTORE_TEXT_SELECTED_COLOR;
extern int VITABACKUP_RESTORE_TEXT_START_COLOR;
// Backup Menu
extern int BACKUP_MENU_COLOR;
extern int VITABACKUP_BACKUPMENU_TIITLE_TEXT_COLOR;
extern int VITABACKUP_BACKUPMENU_TEXT_COLOR;
extern int VITABACKUP_BACKUPMENU_TEXT_SELECTED_COLOR;
extern int VITABACKUP_BACKUPMENU_TEXT_START_COLOR;

// ForeCast colors
extern int FORECAST_NAME_COLOR;
extern int FORECAST_TEMP_COLOR;
extern int FORECAST_TEMP_MIN_COLOR;
extern int FORECAST_TEMP_MAX_COLOR;
extern int FORECAST_WIND_COLOR;
extern int FORECAST_DESC_COLOR;
extern int FORECAST_HUMID_COLOR;
extern int FORECAST_CLOUD_COLOR;
extern int FORECAST_ATMOS_COLOR;
////////////////////////////////////

// Shell colors
extern int VITASHELL_MENU_COLOR;  // BMK
extern int TITLE_COLOR;
extern int PATH_COLOR;
extern int DATE_TIME_COLOR;
extern int BATTERY_PERCENT_COLOR; //BMK
// Storage colors (BMK)
extern int STORAGE_BORDER_COLOR; // BMK
extern int STORAGE_INSIDE_COLOR; // BMK
extern int STORAGE_BAR_COLOR; // BMK

// Settings colors
extern int SETTINGS_MENU_COLOR;
extern int SETTINGS_MENU_FOCUS_COLOR;
extern int SETTINGS_MENU_TITLE_COLOR;
extern int SETTINGS_MENU_ITEM_COLOR;
extern int SETTINGS_MENU_OPTION_COLOR;

// File browser colors
extern int FOCUS_COLOR;
extern int FILE_COLOR;
extern int SFO_COLOR;
extern int TXT_COLOR;
extern int FOLDER_COLOR;
extern int IMAGE_COLOR;
extern int ARCHIVE_COLOR;
extern int SCROLL_BAR_COLOR;
extern int SCROLL_BAR_BG_COLOR;
extern int MARKED_COLOR;
extern int FILE_SYMLINK_COLOR;
extern int FOLDER_SYMLINK_COLOR;

// Context menu colors
extern int CONTEXT_MENU_TEXT_COLOR;
extern int CONTEXT_MENU_FOCUS_COLOR;
extern int CONTEXT_MENU_COLOR;
extern int CONTEXT_MENU_MORE_COLOR;
extern int INVISIBLE_COLOR;

// Dialog colors
extern int DIALOG_COLOR;
extern int DIALOG_BG_COLOR;
extern int PROGRESS_BAR_COLOR;
extern int PROGRESS_BAR_BG_COLOR;

// Hex editor colors
extern int HEX_COLOR;
extern int HEX_OFFSET_COLOR;
extern int HEX_NIBBLE_COLOR;

// Text editor colors
extern int TEXT_COLOR;
extern int TEXT_FOCUS_COLOR;
extern int TEXT_LINE_NUMBER_COLOR;
extern int TEXT_LINE_NUMBER_COLOR_FOCUS;
extern int TEXT_HIGHLIGHT_COLOR;

// Photo viewer colors
extern int PHOTO_ZOOM_COLOR;

// Audio player colors
extern int AUDIO_INFO_ASSIGN;
extern int AUDIO_INFO;
extern int AUDIO_SPEED;
extern int AUDIO_TIME_CURRENT;
extern int AUDIO_TIME_SLASH;
extern int AUDIO_TIME_TOTAL;
extern int AUDIO_TIME_BAR;
extern int AUDIO_TIME_BAR_BG;

extern vita2d_texture *folder_icon, *file_icon, *archive_icon, *image_icon, *audio_icon, *sfo_icon, *text_icon,
            *ftp_image, *dialog_image, *context_image, *context_more_image, *settings_image, *battery_image,
            *battery_bar_red_image, *battery_bar_green_image, *battery_bar_charge_image, *bg_browser_image, *bg_hex_image, *bg_text_image,
            *bg_photo_image, *bg_audio_image, *cover_image, *play_image, *pause_image,
			*fastforward_image, *fastrewind_image, *folder_symlink_icon, *file_symlink_icon,
			*no_cover_image, *bg_book_image, *splashScreen, *no_preview, *database_image, *bg_select_theme_image, *drive_image, *vtb_main_image, *credit_image, // BMK
			*ico_appmenu_vitaident, *ico_appmenu_vitabackup, *ico_appmenu_forecast, *ico_appmenu_database, *ico_appmenu_options, *ico_appmenu_power, *ico_appmenu_shell, *ico_appmenu_credit, *ico_appmenu_file_transfer, *ico_appmenu_books, // BMK
			*ico_menupower_reboot, *ico_menupower_shutdown, *ico_menupower_standby, *ico_menupower_vtb_restart, *vitabackup_image, *vitarestore_image, *vitabackup2_image, //BMK
			*dClearSky, *dClouds, *dRain, *dThunderstorm, *dSnow, *nClearSky, *nClouds, *nRain, *nThunderstorm, *nSnow, *background, *mist, //BMK
			*ico_main_backup, *ico_main_restore, //BMK
			*vitaident_image, *ico_battery_menu, *ico_config_menu, *ico_kernel_menu, *ico_misc_menu, *ico_psn_menu, *ico_storage_menu, *ico_system_menu, *ico_wifi_menu, //BMK
			*scroll_bg, *scroll_pointer, *checkbox_full, *checkbox_empty, *checkbox_full_selected, *checkbox_empty_selected, *ico_container_zip_selected, *ico_container_zip, // BMK
			*help_image, *help_cross, *help_square, *help_circle, *help_triangle, *help_r_analog, *help_pad, *help_lr, *help_select, *help_start; // BMK

extern vita2d_texture *wallpaper_image[MAX_WALLPAPERS]; //BMK
extern vita2d_texture *previous_wallpaper_image, *current_wallpaper_image, *filter_wallpaper_image; //BMK
extern int wallpaper_count; //BMK

extern vita2d_texture *filter_vitashell_wallpaper_image; //BMK

/*extern vita2d_texture *wallpaper_vitashell_image[MAX_WALLPAPERS]; //BMK
extern vita2d_texture *previous_vitashell_wallpaper_image, *current_vitashell_wallpaper_image, *filter_vitashell_wallpaper_image; //BMK
extern int wallpaper_vitashell_count; //BMK*/

void loadTheme();

#endif
