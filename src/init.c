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
#include "browser.h"
#include "init.h"
#include "file.h"
#include "package_installer.h"
#include "utils.h"
#include "touch.h"
#include "qr.h"
#include "rif.h"

#include "audio/vita_audio.h"
//#include "atrac/sound.h"

INCLUDE_EXTERN_RESOURCE(english_us_txt);
INCLUDE_EXTERN_RESOURCE(french_txt);

INCLUDE_EXTERN_RESOURCE(theme_txt);

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

INCLUDE_EXTERN_RESOURCE(changeinfo_fr_txt);
INCLUDE_EXTERN_RESOURCE(changeinfo_en_txt);

INCLUDE_EXTERN_RESOURCE(changeinfo_xml);
INCLUDE_EXTERN_RESOURCE(changeinfo_02_xml);

INCLUDE_EXTERN_RESOURCE(umass_skprx);

extern unsigned char _binary_src_modules_kernel_kernel_skprx_start;
extern unsigned char _binary_src_modules_kernel_kernel_skprx_size;
extern unsigned char _binary_src_modules_user_user_suprx_start;
extern unsigned char _binary_src_modules_user_user_suprx_size;
extern unsigned char _binary_src_modules_patch_patch_skprx_start;
extern unsigned char _binary_src_modules_patch_patch_skprx_size;
extern unsigned char _binary_src_modules_usbdevice_usbdevice_skprx_start;
extern unsigned char _binary_src_modules_usbdevice_usbdevice_skprx_size;

#define DEFAULT_FILE(path, name, replace) { path, (void *)&_binary_resources_##name##_start, (int)&_binary_resources_##name##_size, replace }

static DefaultFile default_files[] = {
  DEFAULT_FILE("ux0:VitaTweakBox/language/english_us.txt", english_us_txt, 0),
  DEFAULT_FILE("ux0:VitaTweakBox/language/french.txt", french_txt, 0),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/theme.txt", theme_txt, 0),

  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/colors.ini", default_vitashell_colors_ini, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/archive_icon.png", default_vitashell_archive_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/audio_icon.png", default_vitashell_audio_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/battery.png", default_vitashell_battery_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/battery_bar_charge.png", default_vitashell_battery_bar_charge_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/battery_bar_green.png", default_vitashell_battery_bar_green_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/battery_bar_red.png", default_vitashell_battery_bar_red_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/bg_audioplayer.png", default_vitashell_bg_audioplayer_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/bg_browser.png", default_vitashell_bg_browser_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/bg_hexeditor.png", default_vitashell_bg_hexeditor_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/bg_photoviewer.png", default_vitashell_bg_photoviewer_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/bg_texteditor.png", default_vitashell_bg_texteditor_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/context.png", default_vitashell_context_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/context_more.png", default_vitashell_context_more_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/cover.png", default_vitashell_cover_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/dialog.png", default_vitashell_dialog_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/fastforward.png", default_vitashell_fastforward_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/fastrewind.png", default_vitashell_fastrewind_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/file_icon.png", default_vitashell_file_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/file_symlink_icon.png",default_vitashell_file_symlink_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/folder_icon.png", default_vitashell_folder_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/folder_symlink_icon.png",default_vitashell_folder_symlink_icon_png,  1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/ftp.png", default_vitashell_ftp_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/image_icon.png", default_vitashell_image_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/pause.png", default_vitashell_pause_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/play.png", default_vitashell_play_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/settings.png", default_vitashell_settings_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/sfo_icon.png", default_vitashell_sfo_icon_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitashell/text_icon.png", default_vitashell_text_icon_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/colors.ini", default_vtb_colors_ini, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/param.ini", default_vtb_param_ini, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/bg_selecttheme.png", default_vtb_bg_selecttheme_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/preview.png", default_vtb_preview_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/no_preview.png", default_vtb_no_preview_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/no_cover.png", default_vtb_no_cover_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/square.png", default_vtb_square_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/triangle.png", default_vtb_triangle_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/database.png", default_vtb_database_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/credits.png", default_vtb_credits_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/book.png", default_vtb_book_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/vtb_main.png", default_vtb_vtb_main_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_vitaident.png", default_vtb_ico_menu_vitaident_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_vitabackup.png", default_vtb_ico_menu_vitabackup_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_forecast.png", default_vtb_ico_menu_forecast_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_database.png", default_vtb_ico_menu_database_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_options.png", default_vtb_ico_menu_options_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_power.png", default_vtb_ico_menu_power_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_shell.png", default_vtb_ico_menu_shell_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_credit.png", default_vtb_ico_menu_credit_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_file_transfer.png", default_vtb_ico_menu_file_transfer_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_menu_books.png", default_vtb_ico_menu_books_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_power_reboot.png", default_vtb_ico_power_reboot_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_power_shutdown.png", default_vtb_ico_power_shutdown_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_power_standby.png", default_vtb_ico_power_standby_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vtb/ico_power_vtb_restart.png", default_vtb_ico_power_vtb_restart_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/day/dClearSky.png", default_forecast_day_dClearSky_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/day/dClouds.png", default_forecast_day_dClouds_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/day/dRain.png", default_forecast_day_dRain_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/day/dThunderstorm.png", default_forecast_day_dThunderstorm_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/day/dSnow.png", default_forecast_day_dSnow_png, 1),	
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/night/nClearSky.png", default_forecast_night_nClearSky_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/night/nClouds.png", default_forecast_night_nClouds_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/night/nRain.png", default_forecast_night_nRain_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/night/nThunderstorm.png", default_forecast_night_nThunderstorm_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/night/nSnow.png", default_forecast_night_nSnow_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/background.png", default_forecast_background_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/forecast/mist.png", default_forecast_mist_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/vitabackup.png", default_vitabackup_vitabackup_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/restore.png", default_vitabackup_restore_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/backup.png", default_vitabackup_backup_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/scroll_bg.png", default_vitabackup_scroll_bg_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/scroll_pointer.png", default_vitabackup_scroll_pointer_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/checkbox_full.png", default_vitabackup_checkbox_full_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/checkbox_empty.png", default_vitabackup_checkbox_empty_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/checkbox_full_selected.png", default_vitabackup_checkbox_full_selected_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/checkbox_empty_selected.png", default_vitabackup_checkbox_empty_selected_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/ico_container_zip_selected.png", default_vitabackup_ico_container_zip_selected_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/ico_container_zip.png", default_vitabackup_ico_container_zip_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/ico_main_backup.png", default_vitabackup_ico_main_backup_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitabackup/ico_main_restore.png", default_vitabackup_ico_main_restore_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/vitaident.png", default_vitaident_vitaident_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/drive.png", default_vitaident_drive_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_battery_menu.png", default_vitaident_ico_battery_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_config_menu.png", default_vitaident_ico_config_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_kernel_menu.png", default_vitaident_ico_kernel_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_misc_menu.png", default_vitaident_ico_misc_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_psn_menu.png", default_vitaident_ico_psn_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_storage_menu.png", default_vitaident_ico_storage_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_system_menu.png", default_vitaident_ico_system_menu_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/vitaident/ico_wifi_menu.png", default_vitaident_ico_wifi_menu_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_cross.png", default_help_help_cross_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_circle.png", default_help_help_circle_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_square.png", default_help_help_square_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_triangle.png", default_help_help_triangle_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_r_analog.png", default_help_help_r_analog_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_pad.png", default_help_help_pad_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_lr.png", default_help_help_lr_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_select.png", default_help_help_select_png, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/theme/Default/help/help_start.png", default_help_help_start_png, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/changeinfo/changeinfo_fr.txt", changeinfo_fr_txt, 1),
  DEFAULT_FILE("ux0:VitaTweakBox/changeinfo/changeinfo_en.txt", changeinfo_en_txt, 1),
  
  DEFAULT_FILE("ux0:patch/VITATWEAK/sce_sys/changeinfo/changeinfo.xml", changeinfo_xml, 1),
  DEFAULT_FILE("ux0:patch/VITATWEAK/sce_sys/changeinfo/changeinfo_02.xml", changeinfo_02_xml, 1),
  
  DEFAULT_FILE("ux0:VitaTweakBox/module/umass.skprx", umass_skprx, 1),
  
  { "ux0:VitaTweakBox/module/kernel.skprx",    (void *)&_binary_src_modules_kernel_kernel_skprx_start,
                                               (int)&_binary_src_modules_kernel_kernel_skprx_size, 1 },
  { "ux0:VitaTweakBox/module/user.suprx",      (void *)&_binary_src_modules_user_user_suprx_start,
                                               (int)&_binary_src_modules_user_user_suprx_size, 1 },
  { "ux0:VitaTweakBox/module/patch.skprx",     (void *)&_binary_src_modules_patch_patch_skprx_start,
                                               (int)&_binary_src_modules_patch_patch_skprx_size, 1 },
  { "ux0:VitaTweakBox/module/usbdevice.skprx", (void *)&_binary_src_modules_usbdevice_usbdevice_skprx_start,
                                               (int)&_binary_src_modules_usbdevice_usbdevice_skprx_size, 1 },
};

char vitashell_titleid[12];

int is_safe_mode = 0;

SceUID patch_modid = -1, kernel_modid = -1, user_modid = -1;

// System params
int language = 0, enter_button = 0, date_format = 0, time_format = 0;

int isSafeMode() {
  return is_safe_mode;
}

static void initSceAppUtil() {
  // Init SceAppUtil
  SceAppUtilInitParam init_param;
  SceAppUtilBootParam boot_param;
  memset(&init_param, 0, sizeof(SceAppUtilInitParam));
  memset(&boot_param, 0, sizeof(SceAppUtilBootParam));
  sceAppUtilInit(&init_param, &boot_param);

  // Mount
  sceAppUtilMusicMount();
  sceAppUtilPhotoMount();

  // System params
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, &language);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, &enter_button);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_DATE_FORMAT, &date_format);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_TIME_FORMAT, &time_format);

  // Set common dialog config
  SceCommonDialogConfigParam config;
  sceCommonDialogConfigParamInit(&config);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_LANG, (int *)&config.language);
  sceAppUtilSystemParamGetInt(SCE_SYSTEM_PARAM_ID_ENTER_BUTTON, (int *)&config.enterButtonAssign);
  sceCommonDialogSetConfigParam(&config);
}

static void finishSceAppUtil() {
  // Unmount
  sceAppUtilPhotoUmount();
  sceAppUtilMusicUmount();

  // Shutdown AppUtil
  sceAppUtilShutdown();
}

static int isKoreanChar(unsigned int c) {
  unsigned short ch = c;

  // Hangul compatibility jamo block
  if (0x3130 <= ch && ch <= 0x318F) {
    return 1;
  }

  // Hangul syllables block
  if (0xAC00 <= ch && ch <= 0xD7AF) {
    return 1;
  }

  // Korean won sign
  if (ch == 0xFFE6) {
    return 1;
  }

  return 0;
}

static int isLatinChar(unsigned int c) {
  unsigned short ch = c;

  // Basic latin block + latin-1 supplement block
  if (ch <= 0x00FF) {
    return 1;
  }

  // Cyrillic block
  if (0x0400 <= ch && ch <= 0x04FF) {
    return 1;
  }

  return 0;
}

vita2d_pgf *loadSystemFonts() {
  vita2d_system_pgf_config configs[] = {
    { SCE_FONT_LANGUAGE_KOREAN, isKoreanChar },
    { SCE_FONT_LANGUAGE_LATIN, isLatinChar },
    { SCE_FONT_LANGUAGE_DEFAULT, NULL },
  };

  return vita2d_load_system_pgf(3, configs);
}

static void initVita2dLib() {
  vita2d_init();
}

static void finishVita2dLib() {
  vita2d_free_pgf(font);
  vita2d_fini();

  font = NULL;
}

static int initSQLite() {
  return sqlite_init();
}

static int finishSQLite() {
  return sqlite_exit();
}

#define NET_MEMORY_SIZE (4 * 1024 * 1024)

static char *net_memory = NULL;

static void initNet() {
  net_memory = malloc(NET_MEMORY_SIZE);

  SceNetInitParam param;
  param.memory = net_memory;
  param.size = NET_MEMORY_SIZE;
  param.flags = 0;

  sceNetInit(&param);
  sceNetCtlInit();

  sceSslInit(300 * 1024);
  sceHttpInit(40 * 1024);

  sceHttpsDisableOption(SCE_HTTPS_FLAG_SERVER_VERIFY);

  sceNetAdhocInit();

  SceNetAdhocctlAdhocId adhocId;
  memset(&adhocId, 0, sizeof(SceNetAdhocctlAdhocId));
  adhocId.type = SCE_NET_ADHOCCTL_ADHOCTYPE_RESERVED;
  memcpy(&adhocId.data[0], VITASHELL_TITLEID, SCE_NET_ADHOCCTL_ADHOCID_LEN);
  sceNetAdhocctlInit(&adhocId);
}

static void finishNet() {
  sceNetAdhocctlTerm();
  sceNetAdhocTerm();
  sceSslTerm();
  sceHttpTerm();
  sceNetCtlTerm();
  sceNetTerm();
  free(net_memory);
}

void installDefaultFiles() {
  // Make VitaTweakBox folders
  sceIoMkdir("ux0:VitaTweakBox", 0777);
  sceIoMkdir("ux0:VitaTweakBox/changeinfo", 0777);
  sceIoMkdir("ux0:VitaTweakBox/internal", 0777);
  sceIoMkdir("ux0:VitaTweakBox/language", 0777);
  sceIoMkdir("ux0:VitaTweakBox/module", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/forecast", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/forecast/day", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/forecast/night", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/vitabackup", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/vitaident", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/vitashell", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/help", 0777);
  sceIoMkdir("ux0:VitaTweakBox/theme/Default/vtb", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/Database", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/Database/logs", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/Forecast", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/Vitabackup", 0777);
  sceIoMkdir("ux0:VitaTweakBox/tweaks/Vitabackup/backups", 0777);
  
  sceIoMkdir("ux0:patch", 0006);
  sceIoMkdir("ux0:patch/VITATWEAK", 0006);
  sceIoMkdir("ux0:patch/VITATWEAK/sce_sys", 0006);
  sceIoMkdir("ux0:patch/VITATWEAK/sce_sys/changeinfo", 0006);

  // Write default files if they don't exist
  int i;
  for (i = 0; i < (sizeof(default_files) / sizeof(DefaultFile)); i++) {
    SceIoStat stat;
    memset(&stat, 0, sizeof(stat));
    if (sceIoGetstat(default_files[i].path, &stat) < 0 || (default_files[i].replace && (int)stat.st_size != default_files[i].size))
      WriteFile(default_files[i].path, default_files[i].buffer, default_files[i].size);
  }  
}

void creatBookFiles() {
	// Make Books folders
	sceIoMkdir("ux0:books", 0777);
}

void initVitaShell() {
  // Set CPU to 444mhz
  scePowerSetArmClockFrequency(444);

  // Init SceShellUtil events
  sceShellUtilInitEvents(0);

  // Prevent automatic CMA connection
  sceShellUtilLock(SCE_SHELL_UTIL_LOCK_TYPE_USB_CONNECTION);

  // Get titleid
  memset(vitashell_titleid, 0, sizeof(vitashell_titleid));
  sceAppMgrAppParamGetString(sceKernelGetProcessId(), 12, vitashell_titleid, sizeof(vitashell_titleid));

  // Allow writing to ux0:app/VITASHELL
  sceAppMgrUmount("app0:");
  sceAppMgrUmount("savedata0:");

  // Is safe mode
  if (sceIoDevctl("ux0:", 0x3001, NULL, 0, NULL, 0) == 0x80010030)
    is_safe_mode = 1;

  // Set sampling mode
  sceCtrlSetSamplingMode(SCE_CTRL_MODE_ANALOG);
  
  // Load modules
  sceSysmoduleLoadModule(SCE_SYSMODULE_VIDEO_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PGF);
  sceSysmoduleLoadModule(SCE_SYSMODULE_MUSIC_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PHOTO_EXPORT);
  sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
  sceSysmoduleLoadModule(SCE_SYSMODULE_HTTPS);
  sceSysmoduleLoadModule(SCE_SYSMODULE_PSPNET_ADHOC);
  sceSysmoduleLoadModule(SCE_SYSMODULE_SQLITE);
  sceSysmoduleLoadModule(SCE_SYSMODULE_ATRAC);

  // Touch init
  TouchFront_Init();
  TouchBack_Init();
  
  // Init
  //soundInit();
  vitaAudioInit(0x40);
  //soundInit();
  initVita2dLib();
  initSceAppUtil();
  initNet();
  initQR();
  initSQLite();

  // Init power tick thread
  initPowerTickThread();

  // Delete vitatweakbox updater if available
  if (checkAppExist("VSUPDATER")) {
    deleteApp("VSUPDATER");
  }

  // Install default files
  installDefaultFiles();
  
  // Install folder files
  if(!checkFileExist("ux0:books")){
	creatBookFiles();
  }

  // Load modules
    int search_unk[2];
  SceUID search_modid;
  search_modid = _vshKernelSearchModuleByName("VitaShellPatch", search_unk);
  if(search_modid < 0) {
    patch_modid = taiLoadKernelModule("ux0:VitaTweakBox/module/patch.skprx", 0, NULL);
    if (patch_modid >= 0) {
      int res = taiStartKernelModule(patch_modid, 0, NULL, 0, NULL, NULL);
      if (res < 0)
        taiStopUnloadKernelModule(patch_modid, 0, NULL, 0, NULL, NULL);
    }
  }
  search_modid = _vshKernelSearchModuleByName("VitaShellKernel2", search_unk);
  if(search_modid < 0) {
    kernel_modid = taiLoadKernelModule("ux0:VitaTweakBox/module/kernel.skprx", 0, NULL);
    if (kernel_modid >= 0) {
      int res = taiStartKernelModule(kernel_modid, 0, NULL, 0, NULL, NULL);
      if (res < 0)
        taiStopUnloadKernelModule(kernel_modid, 0, NULL, 0, NULL, NULL);
    }
  }
  user_modid = sceKernelLoadStartModule("ux0:VitaTweakBox/module/user.suprx", 0, NULL, 0, NULL, NULL);

  // clear up recent folder frequently
  SceIoStat stat;
  SceDateTime now;
  sceRtcGetCurrentClock(&now, 0);
  int res = sceIoGetstat(VITASHELL_RECENT_PATH, &stat);
  if (res >= 0) {
    if (now.year * 365 + now.day - stat.st_ctime.year * 365 - stat.st_ctime.day
        >= VITASHELL_RECENT_PATH_DELETE_INTERVAL_DAYS) {
      removePath(VITASHELL_RECENT_PATH, 0);
    }
  }

  if (!checkFolderExist(VITASHELL_BOOKMARKS_PATH)) {
    sceIoMkdir(VITASHELL_BOOKMARKS_PATH, 0777);
  }
  if (!checkFolderExist(VITASHELL_RECENT_PATH)) {
    sceIoMkdir(VITASHELL_RECENT_PATH, 0777);
  }
  time_last_recent_files = 0;
  time_last_bookmarks = 0;
}

void finishVitaShell() {
  // Finish
  finishSQLite();
  finishNet();
  finishSceAppUtil();
  finishVita2dLib();
  finishQR();
  vitaAudioShutdown();
  
  // Unload modules
  sceSysmoduleLoadModule(SCE_SYSMODULE_ATRAC);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_SQLITE);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PSPNET_ADHOC);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTPS);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_NET);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PHOTO_EXPORT);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_MUSIC_EXPORT);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_PGF);
  sceSysmoduleUnloadModule(SCE_SYSMODULE_VIDEO_EXPORT);
}
