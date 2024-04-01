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
#include "init.h"
#include "file.h"
#include "config.h"
#include "theme.h"
#include "utils.h"

/////////////// BMK ////////////////
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_wallpaper_png);

INCLUDE_EXTERN_RESOURCE(default_vitashell_colors_ini);
INCLUDE_EXTERN_RESOURCE(default_vtb_param_ini);
INCLUDE_EXTERN_RESOURCE(default_vtb_colors_ini);

INCLUDE_EXTERN_RESOURCE(default_vitashell_archive_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_audio_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_battery_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_battery_bar_charge_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_battery_bar_green_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_battery_bar_red_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_audioplayer_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_browser_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_hexeditor_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_photoviewer_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_bg_texteditor_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_context_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_context_more_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_cover_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_dialog_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_fastforward_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_fastrewind_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_file_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_file_symlink_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_folder_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_folder_symlink_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_ftp_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_image_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_pause_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_play_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_settings_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_sfo_icon_png);
INCLUDE_EXTERN_RESOURCE(default_vitashell_text_icon_png);

INCLUDE_EXTERN_RESOURCE(default_vtb_bg_selecttheme_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_database_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_credits_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_book_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_vtb_main_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_preview_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_no_preview_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_no_cover_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_square_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_triangle_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_vitaident_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_vitabackup_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_forecast_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_database_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_options_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_power_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_shell_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_credit_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_file_transfer_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_menu_books_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_power_reboot_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_power_shutdown_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_power_standby_png);
INCLUDE_EXTERN_RESOURCE(default_vtb_ico_power_vtb_restart_png);

INCLUDE_EXTERN_RESOURCE(default_vitaident_vitaident_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_drive_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_battery_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_config_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_kernel_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_misc_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_psn_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_storage_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_system_menu_png);
INCLUDE_EXTERN_RESOURCE(default_vitaident_ico_wifi_menu_png);

INCLUDE_EXTERN_RESOURCE(default_vitabackup_vitabackup_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_restore_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_backup_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_scroll_bg_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_scroll_pointer_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_checkbox_full_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_checkbox_empty_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_checkbox_full_selected_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_checkbox_empty_selected_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_ico_container_zip_selected_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_ico_container_zip_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_ico_main_backup_png);
INCLUDE_EXTERN_RESOURCE(default_vitabackup_ico_main_restore_png);

INCLUDE_EXTERN_RESOURCE(default_forecast_day_dClearSky_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_day_dClouds_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_day_dRain_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_day_dThunderstorm_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_day_dSnow_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_night_nClearSky_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_night_nClouds_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_night_nRain_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_night_nThunderstorm_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_night_nSnow_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_background_png);
INCLUDE_EXTERN_RESOURCE(default_forecast_mist_png);

INCLUDE_EXTERN_RESOURCE(default_help_help_cross_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_circle_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_square_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_triangle_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_r_analog_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_pad_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_lr_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_select_png);
INCLUDE_EXTERN_RESOURCE(default_help_help_start_png);

// THEME POSITION & SIZE
int NAME_X_POSITION;
int NAME_Y_POSITION;
int NAME_CENTER_DIM;
int NAME_SIZE;
int PREVIEW_X_POSITION;
int PREVIEW_Y_POSITION;
int SCALE_X_POSITION;
int SCALE_Y_POSITION;
int FILTER_R_COLOR;
int FILTER_G_COLOR;
int FILTER_B_COLOR;
int FILTER_A_COLOR;
int FILTER_RW;
int FILTER_RH;
int FILTER_ACTIVE;
// VTB Menu Colors (epileptik)
int VTB_MENU_R;
int VTB_MENU_G;
int VTB_MENU_B;
// Vitaident Menu Colors (epileptik)
int VITAIDENT_MENU_R;
int VITAIDENT_MENU_G;
int VITAIDENT_MENU_B;
// Power Menu Colors (epileptik)
int POWER_MENU_R;
int POWER_MENU_G;
int POWER_MENU_B;
// Vitabackup Menu Colors (epileptik)
int VITABACKUP_MENU_R;
int VITABACKUP_MENU_G;
int VITABACKUP_MENU_B;
// Help Menu POSITION
// HelpBrowser
int HELP_BROWSER_CIRCLE_X;
int HELP_BROWSER_CIRCLE_Y;
int HELP_BROWSER_CROSS_X;
int HELP_BROWSER_CROSS_Y;
int HELP_BROWSER_SQUARE_X;
int HELP_BROWSER_SQUARE_Y;
int HELP_BROWSER_TRIANGLE_X;
int HELP_BROWSER_TRIANGLE_Y;
int HELP_BROWSER_SELECT_X;
int HELP_BROWSER_SELECT_Y;
//int HELP_BROWSER_START_X;
//int HELP_BROWSER_START_Y;
int HELP_BROWSER_CIRCLE_TEXT_X;
int HELP_BROWSER_CIRCLE_TEXT_Y;
int HELP_BROWSER_SQUARE_TEXT_X;
int HELP_BROWSER_SQUARE_TEXT_Y;
int HELP_BROWSER_TRIANGLE_TEXT_X;
int HELP_BROWSER_TRIANGLE_TEXT_Y;
int HELP_BROWSER_CROSS_TEXT_X;
int HELP_BROWSER_CROSS_TEXT_Y;
int HELP_BROWSER_SELECT_TEXT_X;
int HELP_BROWSER_SELECT_TEXT_Y;
//int HELP_BROWSER_START_TEXT_X;
//int HELP_BROWSER_START_TEXT_Y;
// HelpTextEditor
int HELP_TEXTEDITOR_CIRCLE_X;
int HELP_TEXTEDITOR_CIRCLE_Y;
int HELP_TEXTEDITOR_CROSS_X;
int HELP_TEXTEDITOR_CROSS_Y;
int HELP_TEXTEDITOR_SQUARE_X;
int HELP_TEXTEDITOR_SQUARE_Y;
int HELP_TEXTEDITOR_TRIANGLE_X;
int HELP_TEXTEDITOR_TRIANGLE_Y;
int HELP_TEXTEDITOR_PAD_X;
int HELP_TEXTEDITOR_PAD_Y;
int HELP_TEXTEDITOR_LR_X;
int HELP_TEXTEDITOR_LR_Y;
int HELP_TEXTEDITOR_CIRCLE_TEXT_X;
int HELP_TEXTEDITOR_CIRCLE_TEXT_Y;
int HELP_TEXTEDITOR_SQUARE_TEXT_X;
int HELP_TEXTEDITOR_SQUARE_TEXT_Y;
int HELP_TEXTEDITOR_TRIANGLE_TEXT_X;
int HELP_TEXTEDITOR_TRIANGLE_TEXT_Y;
int HELP_TEXTEDITOR_CROSS_TEXT_X;
int HELP_TEXTEDITOR_CROSS_TEXT_Y;
int HELP_TEXTEDITOR_PAD_TEXT_X;
int HELP_TEXTEDITOR_PAD_TEXT_Y;
int HELP_TEXTEDITOR_LR_TEXT_X;
int HELP_TEXTEDITOR_LR_TEXT_Y;
// HelpHexEditor
int HELP_HEXEDITOR_CIRCLE_X;
int HELP_HEXEDITOR_CIRCLE_Y;
int HELP_HEXEDITOR_CROSS_X;
int HELP_HEXEDITOR_CROSS_Y;
int HELP_HEXEDITOR_SQUARE_X;
int HELP_HEXEDITOR_SQUARE_Y;
int HELP_HEXEDITOR_LR_X;
int HELP_HEXEDITOR_LR_Y;
int HELP_HEXEDITOR_CIRCLE_TEXT_X;
int HELP_HEXEDITOR_CIRCLE_TEXT_Y;
int HELP_HEXEDITOR_SQUARE_TEXT_X;
int HELP_HEXEDITOR_SQUARE_TEXT_Y;
int HELP_HEXEDITOR_CROSS_TEXT_X;
int HELP_HEXEDITOR_CROSS_TEXT_Y;
int HELP_HEXEDITOR_LR_TEXT_X;
int HELP_HEXEDITOR_LR_TEXT_Y;
// HelpPhotoViewer
int HELP_PHOTOVIEWER_CIRCLE_X;
int HELP_PHOTOVIEWER_CIRCLE_Y;
int HELP_PHOTOVIEWER_PAD_X;
int HELP_PHOTOVIEWER_PAD_Y;
int HELP_PHOTOVIEWER_LR_X;
int HELP_PHOTOVIEWER_LR_Y;
int HELP_PHOTOVIEWER_CROSS_X;
int HELP_PHOTOVIEWER_CROSS_Y;
int HELP_PHOTOVIEWER_R_ANALOG_X;
int HELP_PHOTOVIEWER_R_ANALOG_Y;
int HELP_PHOTOVIEWER_CIRCLE_TEXT_X;
int HELP_PHOTOVIEWER_CIRCLE_TEXT_Y;
int HELP_PHOTOVIEWER_PAD_TEXT_X;
int HELP_PHOTOVIEWER_PAD_TEXT_Y;
int HELP_PHOTOVIEWER_LR_TEXT_X;
int HELP_PHOTOVIEWER_LR_TEXT_Y;
int HELP_PHOTOVIEWER_CROSS_TEXT_X;
int HELP_PHOTOVIEWER_CROSS_TEXT_Y;
int HELP_PHOTOVIEWER_R_ANALOG_TEXT_X;
int HELP_PHOTOVIEWER_R_ANALOG_TEXT_Y;
// HelpAudioPlayer
int HELP_AUDIOPLAYER_CIRCLE_X;
int HELP_AUDIOPLAYER_CIRCLE_Y;
int HELP_AUDIOPLAYER_CROSS_X;
int HELP_AUDIOPLAYER_CROSS_Y;
int HELP_AUDIOPLAYER_TRIANGLE_X;
int HELP_AUDIOPLAYER_TRIANGLE_Y;
int HELP_AUDIOPLAYER_PAD_X;
int HELP_AUDIOPLAYER_PAD_Y;
int HELP_AUDIOPLAYER_LR_X;
int HELP_AUDIOPLAYER_LR_Y;
int HELP_AUDIOPLAYER_CIRCLE_TEXT_X;
int HELP_AUDIOPLAYER_CIRCLE_TEXT_Y;
int HELP_AUDIOPLAYER_TRIANGLE_TEXT_X;
int HELP_AUDIOPLAYER_TRIANGLE_TEXT_Y;
int HELP_AUDIOPLAYER_CROSS_TEXT_X;
int HELP_AUDIOPLAYER_CROSS_TEXT_Y;
int HELP_AUDIOPLAYER_PAD_TEXT_X;
int HELP_AUDIOPLAYER_PAD_TEXT_Y;
int HELP_AUDIOPLAYER_LR_TEXT_X;
int HELP_AUDIOPLAYER_LR_TEXT_Y;
// HelpBookViewer
int HELP_BOOK_TRIANGLE_X;
int HELP_BOOK_TRIANGLE_Y;
int HELP_BOOK_PAD_X;
int HELP_BOOK_PAD_Y;
int HELP_BOOK_LR_X;
int HELP_BOOK_LR_Y;
int HELP_BOOK_CROSS_X;
int HELP_BOOK_CROSS_Y;
int HELP_BOOK_R_ANALOG_X;
int HELP_BOOK_R_ANALOG_Y;
int HELP_BOOK_TRIANGLE_TEXT_X;
int HELP_BOOK_TRIANGLE_TEXT_Y;
int HELP_BOOK_PAD_TEXT_X;
int HELP_BOOK_PAD_TEXT_Y;
int HELP_BOOK_LR_TEXT_X;
int HELP_BOOK_LR_TEXT_Y;
int HELP_BOOK_CROSS_TEXT_X;
int HELP_BOOK_CROSS_TEXT_Y;
int HELP_BOOK_R_ANALOG_TEXT_X;
int HELP_BOOK_R_ANALOG_TEXT_Y;

// VTB Menu colors
int VTB_BACKGROUND_COLOR;
int VTB_MENU_VITAIDENT_COLOR;
int VTB_MENU_VITABACKUP_COLOR;
int VTB_MENU_FORECAST_COLOR;
int VTB_MENU_DATABASE_COLOR;
int VTB_MENU_OPTIONS_COLOR;
int VTB_MENU_POWER_COLOR;
int VTB_MENU_SHELL_COLOR;
int VTB_MENU_FILE_TRANSFER_COLOR;
int VTB_MENU_CREDIT_COLOR;
int VTB_MENU_BOOKS_COLOR;

// Book colors
int BOOK_MENU_COLOR;

// HelpMenu colors
int HELP_MENU_COLOR;
int HELP_MENU_ITEM_COLOR;

// PowerMenu colors
int POWERMENU_REBOOT_COLOR;
int POWERMENU_SHUTDOWN_COLOR;
int POWERMENU_STANDBY_COLOR;
int POWERMENU_VTB_REBOOT_COLOR;

// DataBase color
int DATABASE_MENU_COLOR;
int DATABASE_MENU_FOCUS_COLOR;
int DATABASE_MENU_TITLE_COLOR;
int DATABASE_MENU_ITEM_COLOR;
int DATABASE_MENU_OPTION_COLOR;

// Books colors
int BOOK_IMAGES_MENU_COLOR;
int BOOK_NO_IMAGES_COLOR;

// ThemeManager colors
int THEMEMANAGER_ITEM_COLOR;

// Vitaident colors
int VITAIDENT_MENU_COLOR;
int VITAIDENT_TITLE_KERNEL_COLOR;
int VITAIDENT_TITLE_SYSTEM_COLOR;
int VITAIDENT_TITLE_BATTERY_COLOR;
int VITAIDENT_TITLE_STORAGE_COLOR;
int VITAIDENT_TITLE_WIFI_COLOR;
int VITAIDENT_TITLE_MISC_COLOR;
int VITAIDENT_TITLE_CONFIG_COLOR;
int VITAIDENT_TITLE_PSN_COLOR;
int VITAIDENT_KERNEL_NAME_COLOR;
int VITAIDENT_KERNEL_ITEM_COLOR;
int VITAIDENT_SYSTEM_NAME_COLOR;
int VITAIDENT_SYSTEM_ITEM_COLOR;
int VITAIDENT_BATTERY_NAME_COLOR;
int VITAIDENT_BATTERY_ITEM_COLOR;
int VITAIDENT_STORAGE_NAME_COLOR;
int VITAIDENT_STORAGE_ITEM_COLOR;
int VITAIDENT_STORAGE_DEVICE_COLOR;
int VITAIDENT_STORAGE_BORDER_COLOR;
int VITAIDENT_STORAGE_INSIDE_COLOR;
int VITAIDENT_STORAGE_BAR_COLOR;
int VITAIDENT_WIFI_NAME_COLOR;
int VITAIDENT_WIFI_ITEM_COLOR;
int VITAIDENT_WIFI_PROFILE_COLOR;
int VITAIDENT_WIFI_BORDER_COLOR;
int VITAIDENT_WIFI_INSIDE_COLOR;
int VITAIDENT_MISC_NAME_COLOR;
int VITAIDENT_MISC_ITEM_COLOR;
int VITAIDENT_CONFIG_NAME_COLOR;
int VITAIDENT_CONFIG_ITEM_COLOR;
int VITAIDENT_PSN_NAME_COLOR;
int VITAIDENT_PSN_ITEM_COLOR;

// VitaBackup colors
int VITABACKUP_MENU_COLOR;
int VITABACKUP_TEXT_COLOR;
// Restore
int RESTORE_MENU_COLOR;
int VITABACKUP_RESTORE_TIITLE_TEXT_COLOR;
int VITABACKUP_RESTORE_TEXT_COLOR;
int VITABACKUP_RESTORE_TEXT_SELECTED_COLOR;
int VITABACKUP_RESTORE_TEXT_START_COLOR;
// Backup Menu
int BACKUP_MENU_COLOR;
int VITABACKUP_BACKUPMENU_TIITLE_TEXT_COLOR;
int VITABACKUP_BACKUPMENU_TEXT_COLOR;
int VITABACKUP_BACKUPMENU_TEXT_SELECTED_COLOR;
int VITABACKUP_BACKUPMENU_TEXT_START_COLOR;

// ForeCast colors
int FORECAST_NAME_COLOR;
int FORECAST_TEMP_COLOR;
int FORECAST_TEMP_MIN_COLOR;
int FORECAST_TEMP_MAX_COLOR;
int FORECAST_WIND_COLOR;
int FORECAST_DESC_COLOR;
int FORECAST_HUMID_COLOR;
int FORECAST_CLOUD_COLOR;
int FORECAST_ATMOS_COLOR;
////////////////////////////////////

// Shell colors
int VITASHELL_MENU_COLOR;  // BMK
int TITLE_COLOR;
int PATH_COLOR;
int DATE_TIME_COLOR;
int BATTERY_PERCENT_COLOR; //BMK
// Storage colors
int STORAGE_BORDER_COLOR; // BMK
int STORAGE_INSIDE_COLOR; // BMK
int STORAGE_BAR_COLOR; // BMK

// Settings color
int SETTINGS_MENU_COLOR;
int SETTINGS_MENU_FOCUS_COLOR;
int SETTINGS_MENU_TITLE_COLOR;
int SETTINGS_MENU_ITEM_COLOR;
int SETTINGS_MENU_OPTION_COLOR;

// File browser colors
int FOCUS_COLOR;
int FILE_COLOR;
int FILE_SYMLINK_COLOR;
int FOLDER_SYMLINK_COLOR;
int SFO_COLOR;
int TXT_COLOR;
int FOLDER_COLOR;
int IMAGE_COLOR;
int ARCHIVE_COLOR;
int SCROLL_BAR_COLOR;
int SCROLL_BAR_BG_COLOR;
int MARKED_COLOR;

// Context menu colors
int CONTEXT_MENU_TEXT_COLOR;
int CONTEXT_MENU_FOCUS_COLOR;
int CONTEXT_MENU_COLOR;
int CONTEXT_MENU_MORE_COLOR;
int INVISIBLE_COLOR;

// Dialog colors
int DIALOG_COLOR;
int DIALOG_BG_COLOR;
int PROGRESS_BAR_COLOR;
int PROGRESS_BAR_BG_COLOR;

// Hex editor colors
int HEX_COLOR;
int HEX_OFFSET_COLOR;
int HEX_NIBBLE_COLOR;

// Text editor colors
int TEXT_COLOR;
int TEXT_FOCUS_COLOR;
int TEXT_LINE_NUMBER_COLOR;
int TEXT_LINE_NUMBER_COLOR_FOCUS;
int TEXT_HIGHLIGHT_COLOR;

// Photo viewer colors
int PHOTO_ZOOM_COLOR;

// Audio player colors
int AUDIO_INFO_ASSIGN;
int AUDIO_INFO;
int AUDIO_SPEED;
int AUDIO_TIME_CURRENT;
int AUDIO_TIME_SLASH;
int AUDIO_TIME_TOTAL;
int AUDIO_TIME_BAR;
int AUDIO_TIME_BAR_BG;

vita2d_texture *folder_icon = NULL, *folder_symlink_icon = NULL, *file_icon = NULL,*file_symlink_icon = NULL, *archive_icon =NULL, *image_icon = NULL,
			   *audio_icon = NULL, *sfo_icon = NULL, *text_icon = NULL,
			   *ftp_image = NULL, *dialog_image = NULL, *context_image = NULL, *context_more_image = NULL, *settings_image = NULL, *battery_image = NULL,
			   *battery_bar_red_image = NULL, *battery_bar_green_image = NULL, *battery_bar_charge_image = NULL, *bg_browser_image = NULL, *bg_hex_image = NULL, *bg_text_image = NULL,
			   *bg_photo_image = NULL, *bg_audio_image = NULL, *cover_image = NULL, *play_image = NULL, *pause_image = NULL, *fastforward_image = NULL, *fastrewind_image = NULL,
			   *no_cover_image = NULL, *bg_book_image = NULL, *splashScreen = NULL, *no_preview = NULL, *database_image = NULL, *bg_select_theme_image = NULL, *drive_image = NULL, *vtb_main_image = NULL, *credit_image = NULL, // BMK
			   *ico_appmenu_vitaident = NULL, *ico_appmenu_vitabackup = NULL, *ico_appmenu_forecast = NULL, *ico_appmenu_database = NULL, *ico_appmenu_options = NULL, *ico_appmenu_power = NULL, *ico_appmenu_shell = NULL, *ico_appmenu_credit = NULL, *ico_appmenu_file_transfer = NULL, *ico_appmenu_books = NULL, // BMK
			   *ico_menupower_reboot = NULL, *ico_menupower_shutdown = NULL, *ico_menupower_standby = NULL, *ico_menupower_vtb_restart = NULL, *vitabackup_image = NULL, *vitarestore_image = NULL, *vitabackup2_image = NULL, //BMK
			   *dClearSky = NULL, *dClouds = NULL, *dRain = NULL, *dThunderstorm = NULL, *dSnow = NULL, *nClearSky = NULL, *nClouds = NULL, *nRain = NULL, *nThunderstorm = NULL, *nSnow = NULL, *background = NULL, *mist = NULL, //BMK
			   *ico_main_backup = NULL, *ico_main_restore = NULL, //BMK
			   *vitaident_image = NULL, *ico_battery_menu = NULL, *ico_config_menu = NULL, *ico_kernel_menu = NULL, *ico_misc_menu = NULL, *ico_psn_menu = NULL, *ico_storage_menu = NULL, *ico_system_menu = NULL, *ico_wifi_menu = NULL, //BMK
			   *scroll_bg = NULL, *scroll_pointer = NULL, *checkbox_full = NULL, *checkbox_empty = NULL, *checkbox_full_selected = NULL, *checkbox_empty_selected = NULL, *ico_container_zip_selected = NULL, *ico_container_zip = NULL, // BMK
			   *help_image = NULL, *help_cross = NULL, *help_square = NULL, *help_circle = NULL, *help_triangle = NULL, *help_r_analog = NULL, *help_pad = NULL, *help_lr = NULL, *help_select = NULL, *help_start = NULL; // BMK

vita2d_texture *wallpaper_image[MAX_WALLPAPERS]; //BMK
vita2d_texture *previous_wallpaper_image = NULL, *current_wallpaper_image = NULL, *filter_wallpaper_image = NULL; //BMK; //BMK
int wallpaper_count = 0; //BMK

vita2d_texture *filter_vitashell_wallpaper_image = NULL; //BMK

/*vita2d_texture *wallpaper_vitashell_image[MAX_WALLPAPERS]; //BMK
vita2d_texture *previous_vitashell_wallpaper_image = NULL, *current_vitashell_wallpaper_image = NULL, *filter_vitashell_wallpaper_image = NULL; //BMK
int wallpaper_vitashell_count = 0; //BMK*/

vita2d_pgf *font = NULL;
char font_size_cache[256];

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage;

ThemeImage theme_images[] = {
  { "archive_icon.png", &_binary_resources_default_vitashell_archive_icon_png_start, &archive_icon },
  { "audio_icon.png", &_binary_resources_default_vitashell_audio_icon_png_start, &audio_icon },
  { "battery.png", &_binary_resources_default_vitashell_battery_png_start, &battery_image },
  { "battery_bar_charge.png", &_binary_resources_default_vitashell_battery_bar_charge_png_start, &battery_bar_charge_image },
  { "battery_bar_green.png", &_binary_resources_default_vitashell_battery_bar_green_png_start, &battery_bar_green_image },
  { "battery_bar_red.png", &_binary_resources_default_vitashell_battery_bar_red_png_start, &battery_bar_red_image },
  { "bg_audioplayer.png", NULL, &bg_audio_image },
  { "bg_browser.png", NULL, &bg_browser_image },
  { "bg_hexeditor.png", NULL, &bg_hex_image },
  { "bg_photoviewer.png", NULL, &bg_photo_image },
  { "bg_texteditor.png", NULL, &bg_text_image },
  { "context.png", NULL, &context_image },
  { "context_more.png", NULL, &context_more_image },
  { "cover.png", &_binary_resources_default_vitashell_cover_png_start, &cover_image },
  { "dialog.png", NULL, &dialog_image },
  { "fastforward.png", &_binary_resources_default_vitashell_fastforward_png_start, &fastforward_image },
  { "fastrewind.png", &_binary_resources_default_vitashell_fastrewind_png_start, &fastrewind_image },
  { "file_icon.png", &_binary_resources_default_vitashell_file_icon_png_start, &file_icon },
  { "file_symlink_icon.png", &_binary_resources_default_vitashell_file_symlink_icon_png_start, &file_symlink_icon },
  { "folder_icon.png", &_binary_resources_default_vitashell_folder_icon_png_start, &folder_icon },
  { "folder_symlink_icon.png", &_binary_resources_default_vitashell_folder_symlink_icon_png_start, &folder_symlink_icon },
  { "ftp.png", &_binary_resources_default_vitashell_ftp_png_start, &ftp_image },
  { "image_icon.png", &_binary_resources_default_vitashell_image_icon_png_start, &image_icon },
  { "pause.png", &_binary_resources_default_vitashell_pause_png_start, &pause_image },
  { "play.png", &_binary_resources_default_vitashell_play_png_start, &play_image },
  { "settings.png", NULL, &settings_image },
  { "sfo_icon.png", &_binary_resources_default_vitashell_sfo_icon_png_start, &sfo_icon },
  { "text_icon.png", &_binary_resources_default_vitashell_text_icon_png_start, &text_icon },   
};

#define N_THEME_IMAGES (sizeof(theme_images) / sizeof(ThemeImage))

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage2;

ThemeImage2 theme_images2[] = {
  { "dClearSky.png", &_binary_resources_default_forecast_day_dClearSky_png_start, &dClearSky },
  { "dClouds.png", &_binary_resources_default_forecast_day_dClouds_png_start, &dClouds },
  { "dRain.png", &_binary_resources_default_forecast_day_dRain_png_start, &dRain },
  { "dThunderstorm.png", &_binary_resources_default_forecast_day_dThunderstorm_png_start, &dThunderstorm },
  { "dSnow.png", &_binary_resources_default_forecast_day_dSnow_png_start, &dSnow },	
  { "nClearSky.png", &_binary_resources_default_forecast_night_nClearSky_png_start, &nClearSky },
  { "nClouds.png", &_binary_resources_default_forecast_night_nClouds_png_start, &nClouds },
  { "nRain.png", &_binary_resources_default_forecast_night_nRain_png_start, &nRain },
  { "nThunderstorm.png", &_binary_resources_default_forecast_night_nThunderstorm_png_start, &nThunderstorm },
  { "nSnow.png", &_binary_resources_default_forecast_night_nSnow_png_start, &nSnow },
  { "background.png", &_binary_resources_default_forecast_background_png_start, &background },
  { "mist.png", &_binary_resources_default_forecast_mist_png_start, &mist },  
};

#define N_THEME_IMAGES2 (sizeof(theme_images2) / sizeof(ThemeImage2))

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage3;

ThemeImage3 theme_images3[] = {
  { "vitabackup.png", NULL, &vitabackup_image },
  { "restore.png", NULL, &vitarestore_image },
  { "backup.png", NULL, &vitabackup2_image },
  { "scroll_bg.png", &_binary_resources_default_vitabackup_scroll_bg_png_start, &scroll_bg },
  { "scroll_pointer.png", &_binary_resources_default_vitabackup_scroll_pointer_png_start, &scroll_pointer },
  { "checkbox_full_selected.png", &_binary_resources_default_vitabackup_checkbox_full_selected_png_start, &checkbox_full_selected },
  { "checkbox_empty_selected.png", &_binary_resources_default_vitabackup_checkbox_empty_selected_png_start, &checkbox_empty_selected },
  { "checkbox_full.png", &_binary_resources_default_vitabackup_checkbox_full_png_start, &checkbox_full },
  { "checkbox_empty.png", &_binary_resources_default_vitabackup_checkbox_empty_png_start, &checkbox_empty },
  { "ico_container_zip_selected.png", &_binary_resources_default_vitabackup_ico_container_zip_selected_png_start, &ico_container_zip_selected },
  { "ico_container_zip.png", &_binary_resources_default_vitabackup_ico_container_zip_png_start, &ico_container_zip },
  { "ico_main_backup.png", &_binary_resources_default_vitabackup_ico_main_backup_png_start, &ico_main_backup },
  { "ico_main_restore.png", &_binary_resources_default_vitabackup_ico_main_restore_png_start, &ico_main_restore },  
};

#define N_THEME_IMAGES3 (sizeof(theme_images3) / sizeof(ThemeImage3))

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage4;

ThemeImage4 theme_images4[] = {
  { "vitaident.png", NULL, &vitaident_image },
  { "drive.png", &_binary_resources_default_vitaident_drive_png_start, &drive_image },
  { "ico_battery_menu.png", &_binary_resources_default_vitaident_ico_battery_menu_png_start, &ico_battery_menu },
  { "ico_config_menu.png", &_binary_resources_default_vitaident_ico_config_menu_png_start, &ico_config_menu },
  { "ico_kernel_menu.png", &_binary_resources_default_vitaident_ico_kernel_menu_png_start, &ico_kernel_menu },
  { "ico_misc_menu.png", &_binary_resources_default_vitaident_ico_misc_menu_png_start, &ico_misc_menu },
  { "ico_psn_menu.png", &_binary_resources_default_vitaident_ico_psn_menu_png_start, &ico_psn_menu },
  { "ico_storage_menu.png", &_binary_resources_default_vitaident_ico_storage_menu_png_start, &ico_storage_menu },
  { "ico_system_menu.png", &_binary_resources_default_vitaident_ico_system_menu_png_start, &ico_system_menu },
  { "ico_wifi_menu.png", &_binary_resources_default_vitaident_ico_wifi_menu_png_start, &ico_wifi_menu },
};

#define N_THEME_IMAGES4 (sizeof(theme_images4) / sizeof(ThemeImage4))

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage5;

ThemeImage5 theme_images5[] = {
  { "help_cross.png", &_binary_resources_default_help_help_cross_png_start, &help_cross },
  { "help_circle.png", &_binary_resources_default_help_help_circle_png_start, &help_circle },
  { "help_square.png", &_binary_resources_default_help_help_square_png_start, &help_square },
  { "help_triangle.png", &_binary_resources_default_help_help_triangle_png_start, &help_triangle },
  { "help_r_analog.png", &_binary_resources_default_help_help_r_analog_png_start, &help_r_analog },
  { "help_pad.png", &_binary_resources_default_help_help_pad_png_start, &help_pad },
  { "help_lr.png", &_binary_resources_default_help_help_lr_png_start, &help_lr },
  { "help_select.png", &_binary_resources_default_help_help_select_png_start, &help_select },
  { "help_start.png", &_binary_resources_default_help_help_start_png_start, &help_start },
};

#define N_THEME_IMAGES5 (sizeof(theme_images5) / sizeof(ThemeImage5))

typedef struct {
  char *name;
  void *default_buf;
  vita2d_texture **texture;
} ThemeImage6;

ThemeImage6 theme_images6[] = {
  { "preview.png", &_binary_resources_default_vtb_preview_png_start, &splashScreen },
  { "no_preview.png", &_binary_resources_default_vtb_no_preview_png_start, &no_preview },
  { "no_cover.png", &_binary_resources_default_vtb_no_cover_png_start, &no_cover_image },
  //{ "square.png", &_binary_resources_default_vtb_square_png_start, &square },
  //{ "triangle.png", &_binary_resources_default_vtb_triangle_png_start, &triangle },
  { "database.png", NULL, &database_image },
  { "credits.png", &_binary_resources_default_vtb_credits_png_start, &credit_image },
  { "book.png", &_binary_resources_default_vtb_book_png_start, &bg_book_image },
  { "vtb_main.png", NULL, &vtb_main_image },
  { "bg_selecttheme.png", NULL, &bg_select_theme_image },
  { "ico_menu_vitaident.png", &_binary_resources_default_vtb_ico_menu_vitaident_png_start, &ico_appmenu_vitaident },
  { "ico_menu_vitabackup.png", &_binary_resources_default_vtb_ico_menu_vitabackup_png_start, &ico_appmenu_vitabackup },
  { "ico_menu_forecast.png", &_binary_resources_default_vtb_ico_menu_forecast_png_start, &ico_appmenu_forecast },
  { "ico_menu_database.png", &_binary_resources_default_vtb_ico_menu_database_png_start, &ico_appmenu_database },
  { "ico_menu_options.png", &_binary_resources_default_vtb_ico_menu_options_png_start, &ico_appmenu_options },
  { "ico_menu_power.png", &_binary_resources_default_vtb_ico_menu_power_png_start, &ico_appmenu_power },
  { "ico_menu_shell.png", &_binary_resources_default_vtb_ico_menu_shell_png_start, &ico_appmenu_shell },
  { "ico_menu_credit.png", &_binary_resources_default_vtb_ico_menu_credit_png_start, &ico_appmenu_credit },
  { "ico_menu_file_transfer.png", &_binary_resources_default_vtb_ico_menu_file_transfer_png_start, &ico_appmenu_file_transfer },  
  { "ico_menu_books.png", &_binary_resources_default_vtb_ico_menu_books_png_start, &ico_appmenu_books },
  { "ico_power_reboot.png", &_binary_resources_default_vtb_ico_power_reboot_png_start, &ico_menupower_reboot },
  { "ico_power_shutdown.png", &_binary_resources_default_vtb_ico_power_shutdown_png_start, &ico_menupower_shutdown },
  { "ico_power_standby.png", &_binary_resources_default_vtb_ico_power_standby_png_start, &ico_menupower_standby },
  { "ico_power_vtb_restart.png", &_binary_resources_default_vtb_ico_power_vtb_restart_png_start, &ico_menupower_vtb_restart },  
};

#define N_THEME_IMAGES6 (sizeof(theme_images6) / sizeof(ThemeImage6))

void loadTheme() {
  #define COLOR_ENTRY(name) { #name, CONFIG_TYPE_HEXDECIMAL, (void *)&name }
  ConfigEntry colors_entries[] = {
    // Shell colors
	COLOR_ENTRY(VITASHELL_MENU_COLOR), // BMK
    COLOR_ENTRY(TITLE_COLOR),
    COLOR_ENTRY(PATH_COLOR),
    COLOR_ENTRY(DATE_TIME_COLOR),
	COLOR_ENTRY(BATTERY_PERCENT_COLOR), //BMK
	// Storage colors
	COLOR_ENTRY(STORAGE_BORDER_COLOR), // BMK
	COLOR_ENTRY(STORAGE_INSIDE_COLOR), // BMK
	COLOR_ENTRY(STORAGE_BAR_COLOR),    // BMK
	
    // Settings colors
    COLOR_ENTRY(SETTINGS_MENU_COLOR),
    COLOR_ENTRY(SETTINGS_MENU_FOCUS_COLOR),
    COLOR_ENTRY(SETTINGS_MENU_TITLE_COLOR),
    COLOR_ENTRY(SETTINGS_MENU_ITEM_COLOR),
    COLOR_ENTRY(SETTINGS_MENU_OPTION_COLOR),

    // File browser colors
    COLOR_ENTRY(FOCUS_COLOR),
    COLOR_ENTRY(FILE_COLOR),
    COLOR_ENTRY(FILE_SYMLINK_COLOR),
    COLOR_ENTRY(FOLDER_SYMLINK_COLOR),
    COLOR_ENTRY(SFO_COLOR),
    COLOR_ENTRY(TXT_COLOR),
    COLOR_ENTRY(FOLDER_COLOR),
    COLOR_ENTRY(IMAGE_COLOR),
    COLOR_ENTRY(ARCHIVE_COLOR),
    COLOR_ENTRY(SCROLL_BAR_COLOR),
    COLOR_ENTRY(SCROLL_BAR_BG_COLOR),
    COLOR_ENTRY(MARKED_COLOR),

    // Context menu colors
    COLOR_ENTRY(CONTEXT_MENU_TEXT_COLOR),
    COLOR_ENTRY(CONTEXT_MENU_FOCUS_COLOR),
    COLOR_ENTRY(CONTEXT_MENU_COLOR),
    COLOR_ENTRY(CONTEXT_MENU_MORE_COLOR),
    COLOR_ENTRY(INVISIBLE_COLOR),

    // Dialog colors
    COLOR_ENTRY(DIALOG_COLOR),
    COLOR_ENTRY(DIALOG_BG_COLOR),
    COLOR_ENTRY(PROGRESS_BAR_COLOR),
    COLOR_ENTRY(PROGRESS_BAR_BG_COLOR),

    // Hex editor colors
    COLOR_ENTRY(HEX_COLOR),
    COLOR_ENTRY(HEX_OFFSET_COLOR),
    COLOR_ENTRY(HEX_NIBBLE_COLOR),

    // Text editor colors
    COLOR_ENTRY(TEXT_COLOR),
    COLOR_ENTRY(TEXT_FOCUS_COLOR),
    COLOR_ENTRY(TEXT_LINE_NUMBER_COLOR),
    COLOR_ENTRY(TEXT_LINE_NUMBER_COLOR_FOCUS),
    COLOR_ENTRY(TEXT_HIGHLIGHT_COLOR),

    // Photo viewer colors
    COLOR_ENTRY(PHOTO_ZOOM_COLOR),

    // Audio player colors
    COLOR_ENTRY(AUDIO_INFO_ASSIGN),
    COLOR_ENTRY(AUDIO_INFO),
    COLOR_ENTRY(AUDIO_SPEED),
    COLOR_ENTRY(AUDIO_TIME_CURRENT),
    COLOR_ENTRY(AUDIO_TIME_SLASH),
    COLOR_ENTRY(AUDIO_TIME_TOTAL),
    COLOR_ENTRY(AUDIO_TIME_BAR),
    COLOR_ENTRY(AUDIO_TIME_BAR_BG),
  };

  // Load default config file
  readConfigBuffer(&_binary_resources_default_vitashell_colors_ini_start, (int)&_binary_resources_default_vitashell_colors_ini_size, colors_entries, sizeof(colors_entries) / sizeof(ConfigEntry));
  
  #define COLOR_ENTRY(name) { #name, CONFIG_TYPE_HEXDECIMAL, (void *)&name }
  ConfigEntry vtb_colors_entries[] = {
	
	// VTB Menu colors
	COLOR_ENTRY(VTB_BACKGROUND_COLOR),
	COLOR_ENTRY(VTB_MENU_VITAIDENT_COLOR),
	COLOR_ENTRY(VTB_MENU_VITABACKUP_COLOR),
	COLOR_ENTRY(VTB_MENU_FORECAST_COLOR),
	COLOR_ENTRY(VTB_MENU_DATABASE_COLOR),
	COLOR_ENTRY(VTB_MENU_OPTIONS_COLOR),
	COLOR_ENTRY(VTB_MENU_POWER_COLOR),
	COLOR_ENTRY(VTB_MENU_SHELL_COLOR),
	COLOR_ENTRY(VTB_MENU_FILE_TRANSFER_COLOR),
	COLOR_ENTRY(VTB_MENU_CREDIT_COLOR),
	COLOR_ENTRY(VTB_MENU_BOOKS_COLOR),
	
	// Book colors
	COLOR_ENTRY(BOOK_MENU_COLOR),
	
	// HelpMenu colors
	COLOR_ENTRY(HELP_MENU_COLOR),
	COLOR_ENTRY(HELP_MENU_ITEM_COLOR),
	
	// PowerMenu colors
	COLOR_ENTRY(POWERMENU_REBOOT_COLOR),
	COLOR_ENTRY(POWERMENU_SHUTDOWN_COLOR),
	COLOR_ENTRY(POWERMENU_STANDBY_COLOR),
	COLOR_ENTRY(POWERMENU_VTB_REBOOT_COLOR),
	
	// DataBase colors
	COLOR_ENTRY(DATABASE_MENU_COLOR),
	COLOR_ENTRY(DATABASE_MENU_FOCUS_COLOR),
	COLOR_ENTRY(DATABASE_MENU_TITLE_COLOR),
	COLOR_ENTRY(DATABASE_MENU_ITEM_COLOR),
	COLOR_ENTRY(DATABASE_MENU_OPTION_COLOR),
		
	// Books colors
	COLOR_ENTRY(BOOK_IMAGES_MENU_COLOR),
	COLOR_ENTRY(BOOK_NO_IMAGES_COLOR),
		
	// ThemeManager colors
	COLOR_ENTRY(THEMEMANAGER_ITEM_COLOR),
		
	// Vitaident colors
	COLOR_ENTRY(VITAIDENT_MENU_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_KERNEL_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_SYSTEM_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_BATTERY_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_STORAGE_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_WIFI_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_MISC_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_CONFIG_COLOR),
	COLOR_ENTRY(VITAIDENT_TITLE_PSN_COLOR),		
	COLOR_ENTRY(VITAIDENT_KERNEL_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_KERNEL_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_SYSTEM_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_SYSTEM_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_BATTERY_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_BATTERY_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_DEVICE_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_BORDER_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_INSIDE_COLOR),
	COLOR_ENTRY(VITAIDENT_STORAGE_BAR_COLOR),
	COLOR_ENTRY(VITAIDENT_WIFI_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_WIFI_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_WIFI_PROFILE_COLOR),
	COLOR_ENTRY(VITAIDENT_WIFI_BORDER_COLOR),
	COLOR_ENTRY(VITAIDENT_WIFI_INSIDE_COLOR),
	COLOR_ENTRY(VITAIDENT_MISC_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_MISC_ITEM_COLOR),		
	COLOR_ENTRY(VITAIDENT_CONFIG_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_CONFIG_ITEM_COLOR),
	COLOR_ENTRY(VITAIDENT_PSN_NAME_COLOR),
	COLOR_ENTRY(VITAIDENT_PSN_ITEM_COLOR),
		
	// VitaBackup colors
	COLOR_ENTRY(VITABACKUP_MENU_COLOR),
	COLOR_ENTRY(VITABACKUP_TEXT_COLOR),
	// Restore
	COLOR_ENTRY(RESTORE_MENU_COLOR),
	COLOR_ENTRY(VITABACKUP_RESTORE_TIITLE_TEXT_COLOR),
	COLOR_ENTRY(VITABACKUP_RESTORE_TEXT_COLOR),
	COLOR_ENTRY(VITABACKUP_RESTORE_TEXT_SELECTED_COLOR),
	COLOR_ENTRY(VITABACKUP_RESTORE_TEXT_START_COLOR),
	// Backup Menu
	COLOR_ENTRY(BACKUP_MENU_COLOR),
	COLOR_ENTRY(VITABACKUP_BACKUPMENU_TIITLE_TEXT_COLOR),
	COLOR_ENTRY(VITABACKUP_BACKUPMENU_TEXT_COLOR),
	COLOR_ENTRY(VITABACKUP_BACKUPMENU_TEXT_SELECTED_COLOR),
	COLOR_ENTRY(VITABACKUP_BACKUPMENU_TEXT_START_COLOR),
		
	// ForeCast colors
	COLOR_ENTRY(FORECAST_NAME_COLOR),
	COLOR_ENTRY(FORECAST_TEMP_COLOR),
	COLOR_ENTRY(FORECAST_TEMP_MIN_COLOR),
	COLOR_ENTRY(FORECAST_TEMP_MAX_COLOR),
	COLOR_ENTRY(FORECAST_WIND_COLOR),
	COLOR_ENTRY(FORECAST_DESC_COLOR),
	COLOR_ENTRY(FORECAST_HUMID_COLOR),
	COLOR_ENTRY(FORECAST_CLOUD_COLOR),
	COLOR_ENTRY(FORECAST_ATMOS_COLOR),
  };
  
  int i;

  // Load default config file
  readConfigBuffer(&_binary_resources_default_vtb_colors_ini_start, (int)&_binary_resources_default_vtb_colors_ini_size, vtb_colors_entries, sizeof(vtb_colors_entries) / sizeof(ConfigEntry));

  /////////////// BMK ////////////////
	#define POSITION_ENTRY(name) { #name, CONFIG_TYPE_DECIMAL, (void *)&name }
	ConfigEntry position_entries[] = {
		// THEME POSITION
		/*POSITION_ENTRY(SQUARE_X_POSITION),
		POSITION_ENTRY(SQUARE_Y_POSITION),
		POSITION_ENTRY(TRIANGLE_X_POSITION),
		POSITION_ENTRY(TRIANGLE_Y_POSITION),
		POSITION_ENTRY(SELECT_X_POSITION),
		POSITION_ENTRY(SELECT_Y_POSITION),
		POSITION_ENTRY(CANCEL_X_POSITION),
		POSITION_ENTRY(CANCEL_Y_POSITION),*/
		POSITION_ENTRY(NAME_X_POSITION),
		POSITION_ENTRY(NAME_Y_POSITION),
		POSITION_ENTRY(NAME_SIZE),
		POSITION_ENTRY(NAME_CENTER_DIM),
		POSITION_ENTRY(PREVIEW_X_POSITION),
		POSITION_ENTRY(PREVIEW_Y_POSITION),
		POSITION_ENTRY(SCALE_X_POSITION),
		POSITION_ENTRY(SCALE_Y_POSITION),
		POSITION_ENTRY(FILTER_R_COLOR),
		POSITION_ENTRY(FILTER_G_COLOR),
		POSITION_ENTRY(FILTER_B_COLOR),
		POSITION_ENTRY(FILTER_A_COLOR),
		POSITION_ENTRY(FILTER_RW),
		POSITION_ENTRY(FILTER_RH),
		POSITION_ENTRY(FILTER_ACTIVE),
		// VTB Menu Colors (epileptik)
		POSITION_ENTRY(VTB_MENU_R),
		POSITION_ENTRY(VTB_MENU_G),
		POSITION_ENTRY(VTB_MENU_B),
		// Vitaident Menu Colors (epileptik)
		POSITION_ENTRY(VITAIDENT_MENU_R),
		POSITION_ENTRY(VITAIDENT_MENU_G),
		POSITION_ENTRY(VITAIDENT_MENU_B),
		// Power Menu Colors (epileptik)
		POSITION_ENTRY(POWER_MENU_R),
		POSITION_ENTRY(POWER_MENU_G),
		POSITION_ENTRY(POWER_MENU_B),
		// Vitabackup Menu Colors (epileptik)
		POSITION_ENTRY(VITABACKUP_MENU_R),
		POSITION_ENTRY(VITABACKUP_MENU_G),
		POSITION_ENTRY(VITABACKUP_MENU_B),
		// HELP MENU POSITION
		POSITION_ENTRY(HELP_BROWSER_CIRCLE_X),
		POSITION_ENTRY(HELP_BROWSER_CIRCLE_Y),
		POSITION_ENTRY(HELP_BROWSER_CROSS_X),
		POSITION_ENTRY(HELP_BROWSER_CROSS_Y),
		POSITION_ENTRY(HELP_BROWSER_SQUARE_X),
		POSITION_ENTRY(HELP_BROWSER_SQUARE_Y),
		POSITION_ENTRY(HELP_BROWSER_TRIANGLE_X),
		POSITION_ENTRY(HELP_BROWSER_TRIANGLE_Y),
		POSITION_ENTRY(HELP_BROWSER_SELECT_X),
		POSITION_ENTRY(HELP_BROWSER_SELECT_Y),
		//POSITION_ENTRY(HELP_BROWSER_START_X),
		//POSITION_ENTRY(HELP_BROWSER_START_Y),
		POSITION_ENTRY(HELP_BROWSER_CIRCLE_TEXT_X),
		POSITION_ENTRY(HELP_BROWSER_CIRCLE_TEXT_Y),
		POSITION_ENTRY(HELP_BROWSER_SQUARE_TEXT_X),
		POSITION_ENTRY(HELP_BROWSER_SQUARE_TEXT_Y),
		POSITION_ENTRY(HELP_BROWSER_TRIANGLE_TEXT_X),
		POSITION_ENTRY(HELP_BROWSER_TRIANGLE_TEXT_Y),
		POSITION_ENTRY(HELP_BROWSER_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_BROWSER_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_BROWSER_SELECT_TEXT_X),
		POSITION_ENTRY(HELP_BROWSER_SELECT_TEXT_Y),
		//POSITION_ENTRY(HELP_BROWSER_START_TEXT_X),
		//POSITION_ENTRY(HELP_BROWSER_START_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_CIRCLE_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_CIRCLE_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_CROSS_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_CROSS_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_SQUARE_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_SQUARE_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_TRIANGLE_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_TRIANGLE_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_PAD_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_PAD_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_LR_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_LR_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_CIRCLE_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_CIRCLE_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_SQUARE_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_SQUARE_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_TRIANGLE_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_TRIANGLE_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_PAD_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_PAD_TEXT_Y),
		POSITION_ENTRY(HELP_TEXTEDITOR_LR_TEXT_X),
		POSITION_ENTRY(HELP_TEXTEDITOR_LR_TEXT_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_CIRCLE_X),
		POSITION_ENTRY(HELP_HEXEDITOR_CIRCLE_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_CROSS_X),
		POSITION_ENTRY(HELP_HEXEDITOR_CROSS_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_SQUARE_X),
		POSITION_ENTRY(HELP_HEXEDITOR_SQUARE_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_LR_X),
		POSITION_ENTRY(HELP_HEXEDITOR_LR_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_CIRCLE_TEXT_X),
		POSITION_ENTRY(HELP_HEXEDITOR_CIRCLE_TEXT_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_SQUARE_TEXT_X),
		POSITION_ENTRY(HELP_HEXEDITOR_SQUARE_TEXT_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_HEXEDITOR_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_HEXEDITOR_LR_TEXT_X),
		POSITION_ENTRY(HELP_HEXEDITOR_LR_TEXT_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CIRCLE_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CIRCLE_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_PAD_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_PAD_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_LR_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_LR_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CROSS_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CROSS_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_R_ANALOG_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_R_ANALOG_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CIRCLE_TEXT_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CIRCLE_TEXT_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_PAD_TEXT_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_PAD_TEXT_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_LR_TEXT_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_LR_TEXT_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_PHOTOVIEWER_R_ANALOG_TEXT_X),
		POSITION_ENTRY(HELP_PHOTOVIEWER_R_ANALOG_TEXT_Y),
		POSITION_ENTRY(HELP_BOOK_TRIANGLE_X),
		POSITION_ENTRY(HELP_BOOK_TRIANGLE_Y),
		POSITION_ENTRY(HELP_BOOK_PAD_X),
		POSITION_ENTRY(HELP_BOOK_PAD_Y),
		POSITION_ENTRY(HELP_BOOK_LR_X),
		POSITION_ENTRY(HELP_BOOK_LR_Y),
		POSITION_ENTRY(HELP_BOOK_CROSS_X),
		POSITION_ENTRY(HELP_BOOK_CROSS_Y),
		POSITION_ENTRY(HELP_BOOK_R_ANALOG_X),
		POSITION_ENTRY(HELP_BOOK_R_ANALOG_Y),
		POSITION_ENTRY(HELP_BOOK_TRIANGLE_TEXT_X),
		POSITION_ENTRY(HELP_BOOK_TRIANGLE_TEXT_Y),
		POSITION_ENTRY(HELP_BOOK_PAD_TEXT_X),
		POSITION_ENTRY(HELP_BOOK_PAD_TEXT_Y),
		POSITION_ENTRY(HELP_BOOK_LR_TEXT_X),
		POSITION_ENTRY(HELP_BOOK_LR_TEXT_Y),
		POSITION_ENTRY(HELP_BOOK_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_BOOK_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_BOOK_R_ANALOG_TEXT_X),
		POSITION_ENTRY(HELP_BOOK_R_ANALOG_TEXT_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CIRCLE_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CIRCLE_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CROSS_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CROSS_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_TRIANGLE_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_TRIANGLE_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_PAD_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_PAD_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_LR_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_LR_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CIRCLE_TEXT_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CIRCLE_TEXT_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_TRIANGLE_TEXT_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_TRIANGLE_TEXT_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CROSS_TEXT_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_CROSS_TEXT_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_PAD_TEXT_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_PAD_TEXT_Y),
		POSITION_ENTRY(HELP_AUDIOPLAYER_LR_TEXT_X),
		POSITION_ENTRY(HELP_AUDIOPLAYER_LR_TEXT_Y),
		
	};
	////////////////////////////////////

	// Load default config file BMK
	readConfigBuffer(&_binary_resources_default_vtb_param_ini_start, (int)&_binary_resources_default_vtb_param_ini_size, position_entries, sizeof(position_entries) / sizeof(ConfigEntry));
				   
  // Load custom config file
  if (use_custom_config) {
    char path[MAX_PATH_LENGTH];
	/*char path2[MAX_PATH_LENGTH];
	char path3[MAX_PATH_LENGTH];
	char path4[MAX_PATH_LENGTH];*/

    char *theme_name = NULL;
    ConfigEntry theme_entries[] = {
      { "THEME_NAME", CONFIG_TYPE_STRING, (void *)&theme_name },
    };

    // Load theme config
    readConfig("ux0:VitaTweakBox/theme/theme.txt", theme_entries, sizeof(theme_entries) / sizeof(ConfigEntry));

    if (theme_name) {
      // Load colors config
      snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/colors.ini", theme_name);
      readConfig(path, colors_entries, sizeof(colors_entries) / sizeof(ConfigEntry));
	  
	  // Load colors config
      snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/colors.ini", theme_name);
      readConfig(path, vtb_colors_entries, sizeof(vtb_colors_entries) / sizeof(ConfigEntry));
      
	  // Load position config BMK
	  snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/param.ini", theme_name);
	  readConfig(path, position_entries, sizeof(position_entries) / sizeof(ConfigEntry));
	  
      // Font
      snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/font.pgf", theme_name);
      font = vita2d_load_custom_pgf(path);
      
	  /////////////// BMK ////////////////
	  /////////////// Filter VitaShell Wallpapers
	  snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/filter_wallpaper.png", theme_name);
	  vita2d_texture *filter_image = vita2d_load_PNG_file(path);
	  if (filter_image)
	  	filter_vitashell_wallpaper_image = filter_image;
			
	  /////////////// Wallpapers VitaShell
	  /*snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/wallpaper.png", theme_name);
	  vita2d_texture *image = vita2d_load_PNG_file(path);
	  if (image)
		wallpaper_vitashell_image[wallpaper_vitashell_count++] = image;
			
	  int z;
		for (z = 1; z < MAX_WALLPAPERS; z++) {
			snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/wallpaper%d.png", theme_name, z + 1);
			vita2d_texture *image = vita2d_load_PNG_file(path);
			if (image)
				wallpaper_vitashell_image[wallpaper_vitashell_count++] = image;
		}

	  // Set random wallpaper
	  if (wallpaper_vitashell_count > 0) {
		int random_num = randomNumber(0, wallpaper_vitashell_count - 1);
			current_vitashell_wallpaper_image = wallpaper_vitashell_image[random_num];
	  }
	  
	  /////////////// Filter VTB Wallpapers
	  snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/filter_wallpaper.png", theme_name);
	  vita2d_texture *filter_image2 = vita2d_load_PNG_file(path);
	  if (filter_image2)
	  	filter_wallpaper_image = filter_image2;*/
	  
	  /////////////// Wallpapers VTB
	  snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/wallpaper.png", theme_name);
	  vita2d_texture *image2 = vita2d_load_PNG_file(path);
	  if (image2)
		wallpaper_image[wallpaper_count++] = image2;
			
	  int x;
		for (x = 1; x < MAX_WALLPAPERS; x++) {
			snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/wallpaper%d.png", theme_name, x + 1);
			vita2d_texture *image2 = vita2d_load_PNG_file(path);
			if (image2)
				wallpaper_image[wallpaper_count++] = image2;
		}

	  // Set random wallpaper
	  if (wallpaper_count > 0) {
		int random_num = randomNumber(0, wallpaper_count - 1);
			current_wallpaper_image = wallpaper_image[random_num];
	  }
	  ////////////////////////////////////
	  
      // Load theme
      for (i = 0; i < N_THEME_IMAGES; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitashell/%s", theme_name, theme_images[i].name);
        if (theme_images[i].texture && *(theme_images[i].texture) == NULL)
          *(theme_images[i].texture) = vita2d_load_PNG_file(path);
      }
	  for (i = 0; i < N_THEME_IMAGES2; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/forecast/%s", theme_name, theme_images2[i].name);
        if (theme_images2[i].texture && *(theme_images2[i].texture) == NULL)
          *(theme_images2[i].texture) = vita2d_load_PNG_file(path);
      }
	  for (i = 0; i < N_THEME_IMAGES3; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitabackup/%s", theme_name, theme_images3[i].name);
        if (theme_images3[i].texture && *(theme_images3[i].texture) == NULL)
          *(theme_images3[i].texture) = vita2d_load_PNG_file(path);
      }
	  for (i = 0; i < N_THEME_IMAGES4; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vitaident/%s", theme_name, theme_images4[i].name);
        if (theme_images4[i].texture && *(theme_images4[i].texture) == NULL)
          *(theme_images4[i].texture) = vita2d_load_PNG_file(path);
      }
	  for (i = 0; i < N_THEME_IMAGES5; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/help/%s", theme_name, theme_images5[i].name);
        if (theme_images5[i].texture && *(theme_images5[i].texture) == NULL)
          *(theme_images5[i].texture) = vita2d_load_PNG_file(path);
      }
	  for (i = 0; i < N_THEME_IMAGES6; i++) {
        snprintf(path, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/%s", theme_name, theme_images6[i].name);
        if (theme_images6[i].texture && *(theme_images6[i].texture) == NULL)
          *(theme_images6[i].texture) = vita2d_load_PNG_file(path);
      }
    }
  }

  // Load default theme
  for (i = 0; i < N_THEME_IMAGES; i++) {
    if (theme_images[i].texture && *(theme_images[i].texture) == NULL && theme_images[i].default_buf)
      *(theme_images[i].texture) = vita2d_load_PNG_buffer(theme_images[i].default_buf);
  }
  for (i = 0; i < N_THEME_IMAGES2; i++) {
    if (theme_images2[i].texture && *(theme_images2[i].texture) == NULL && theme_images2[i].default_buf)
      *(theme_images2[i].texture) = vita2d_load_PNG_buffer(theme_images2[i].default_buf);
  }
  for (i = 0; i < N_THEME_IMAGES3; i++) {
    if (theme_images3[i].texture && *(theme_images3[i].texture) == NULL && theme_images3[i].default_buf)
      *(theme_images3[i].texture) = vita2d_load_PNG_buffer(theme_images3[i].default_buf);
  }
  for (i = 0; i < N_THEME_IMAGES4; i++) {
    if (theme_images4[i].texture && *(theme_images4[i].texture) == NULL && theme_images4[i].default_buf)
      *(theme_images4[i].texture) = vita2d_load_PNG_buffer(theme_images4[i].default_buf);
  }
  for (i = 0; i < N_THEME_IMAGES5; i++) {
    if (theme_images5[i].texture && *(theme_images5[i].texture) == NULL && theme_images5[i].default_buf)
      *(theme_images5[i].texture) = vita2d_load_PNG_buffer(theme_images5[i].default_buf);
  }
  for (i = 0; i < N_THEME_IMAGES6; i++) {
    if (theme_images6[i].texture && *(theme_images6[i].texture) == NULL && theme_images6[i].default_buf)
      *(theme_images6[i].texture) = vita2d_load_PNG_buffer(theme_images6[i].default_buf);
  }

  // Load default pngs
  if (!dialog_image) {
    dialog_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    void *data = vita2d_texture_get_datap(dialog_image);

    int y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
      int x;
      for (x = 0; x < SCREEN_WIDTH; x++) {
        ((uint32_t *)data)[x + SCREEN_WIDTH * y] = DIALOG_BG_COLOR;
      }
    }
  }

  if (!context_image) {
    context_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    void *data = vita2d_texture_get_datap(context_image);

    int y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
      int x;
      for (x = 0; x < SCREEN_WIDTH; x++) {
        ((uint32_t *)data)[x + SCREEN_WIDTH * y] = CONTEXT_MENU_COLOR;
      }
    }
  }

  if (!context_more_image) {
    context_more_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    void *data = vita2d_texture_get_datap(context_more_image);

    int y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
      int x;
      for (x = 0; x < SCREEN_WIDTH; x++) {
        ((uint32_t *)data)[x + SCREEN_WIDTH * y] = CONTEXT_MENU_MORE_COLOR;
      }
    }
  }

  if (!settings_image) {
    settings_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    void *data = vita2d_texture_get_datap(settings_image);

    int y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
      int x;
      for (x = 0; x < SCREEN_WIDTH; x++) {
        ((uint32_t *)data)[x + SCREEN_WIDTH * y] = SETTINGS_MENU_COLOR;
      }
    }
  }

  /////////////// BMK ////////////////
	if (!database_image) {
		database_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(database_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = DATABASE_MENU_COLOR;
			}
		}
	}
	
	if (!bg_browser_image) {
    bg_browser_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
    void *data = vita2d_texture_get_datap(bg_browser_image);

    int y;
    for (y = 0; y < SCREEN_HEIGHT; y++) {
      int x;
      for (x = 0; x < SCREEN_WIDTH; x++) {
        ((uint32_t *)data)[x + SCREEN_WIDTH * y] = VITASHELL_MENU_COLOR;
      }
    }
  }
	
	if (!credit_image) {
	credit_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(credit_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = 0xE0231f1b;
			}
		}
	}
	
	if (!bg_book_image) {
		bg_book_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(bg_book_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = BOOK_MENU_COLOR;
			}
		}
	}
	
	if (!vitaident_image) {
		vitaident_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(vitaident_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = VITAIDENT_MENU_COLOR;
			}
		}
	}
	
	if (!vitabackup_image) {
		vitabackup_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(vitabackup_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = VITABACKUP_MENU_COLOR;
			}
		}
	}
	
	if (!vitarestore_image) {
		vitarestore_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(vitarestore_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = RESTORE_MENU_COLOR;
			}
		}
	}
	
	if (!vitabackup2_image) {
		vitabackup2_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(vitabackup2_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = BACKUP_MENU_COLOR;
			}
		}
	}
	////////////////////////////////////
  
  // Load system fonts
  if (!font)
    font = loadSystemFonts();

  // Font size cache
  for (i = 0; i < 256; i++) {
    char character[2];
    character[0] = i;
    character[1] = '\0';

    font_size_cache[i] = pgf_text_width(character);
  }
}
