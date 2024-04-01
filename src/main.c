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
#include "main_context.h"
#include "browser.h"
#include "init.h"
#include "io_process.h"
#include "refresh.h"
#include "makezip.h"
#include "package_installer.h"
#include "network_update.h"
#include "network_download.h"
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
#include "book/book.h" //BMK
#include "vitaident/vitaident.h" //BMK
#include "vitaforecast/forecast.h" //BMK
#include "vitaforecast/weather.h" //BMK
#include "vitaforecast/net.h" //BMK
#include "vitabackup/vitabackup.h" //BMK
#include "vitadatabase/database_utils.h" //BMK
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
#include "sfo.h"
#include "coredump.h"
#include "usb.h"
#include "qr.h"
#include "pfs.h"

int archiveOK = 0;

int _newlib_heap_size_user = 128 * 1024 * 1024;

static volatile int dialog_step = DIALOG_STEP_NONE;

static char install_path[MAX_PATH_LENGTH];
static char compress_name[MAX_NAME_LENGTH];

static SceUID usbdevice_modid = -1;

static SceKernelLwMutexWork dialog_mutex;

char vita_ip[16];
unsigned short int vita_port;

VitaShellConfig vitashell_config;

int SCE_CTRL_ENTER = SCE_CTRL_CROSS, SCE_CTRL_CANCEL = SCE_CTRL_CIRCLE;

int use_custom_config = 1;

int getDialogStep() {
  sceKernelLockLwMutex(&dialog_mutex, 1, NULL);
  volatile int step = dialog_step;
  sceKernelUnlockLwMutex(&dialog_mutex, 1);
  return step;
}

void setDialogStep(int step) {
  sceKernelLockLwMutex(&dialog_mutex, 1, NULL);
  dialog_step = step;
  sceKernelUnlockLwMutex(&dialog_mutex, 1);
}

void initFtp() {
  // Add all the current mountpoints to ftpvita
  int i;
  for (i = 0; i < getNumberOfDevices(); i++) {
    char **devices = getDevices();
    if (devices[i]) {
      if (isSafeMode() && strcmp(devices[i], "ux0:") != 0)
        continue;

      ftpvita_add_device(devices[i]);
    }
  }

  ftpvita_ext_add_custom_command("PROM", ftpvita_PROM);
}

void initUsb() {
  char *path = NULL;

  if (vitashell_config.usbdevice == USBDEVICE_MODE_MEMORY_CARD) {
    if (checkFileExist("sdstor0:xmc-lp-ign-userext"))
      path = "sdstor0:xmc-lp-ign-userext";
    else if (checkFileExist("sdstor0:int-lp-ign-userext"))
      path = "sdstor0:int-lp-ign-userext";
    else
      infoDialog(language_container[MEMORY_CARD_NOT_FOUND]);
  } else if (vitashell_config.usbdevice == USBDEVICE_MODE_GAME_CARD) {
    if (checkFileExist("sdstor0:gcd-lp-ign-gamero"))
      path = "sdstor0:gcd-lp-ign-gamero";
    else
      infoDialog(language_container[GAME_CARD_NOT_FOUND]);
  } else if (vitashell_config.usbdevice == USBDEVICE_MODE_SD2VITA) {
    if (checkFileExist("sdstor0:gcd-lp-ign-entire"))
      path = "sdstor0:gcd-lp-ign-entire";
    else
      infoDialog(language_container[MICROSD_NOT_FOUND]);
  } else if (vitashell_config.usbdevice == USBDEVICE_MODE_PSVSD) {
    if (checkFileExist("sdstor0:uma-pp-act-a"))
      path = "sdstor0:uma-pp-act-a";
    else if (checkFileExist("sdstor0:uma-lp-act-entire"))
      path = "sdstor0:uma-lp-act-entire";
    else
      infoDialog(language_container[MICROSD_NOT_FOUND]);
  }

  if (!path)
    return;

  usbdevice_modid = startUsb("ux0:VitaTweakBox/module/usbdevice.skprx", path, SCE_USBSTOR_VSTOR_TYPE_FAT);
  if (usbdevice_modid >= 0) {
    // Lock power timers
    powerLock();
    
    initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL, language_container[USB_CONNECTED]);
    setDialogStep(DIALOG_STEP_USB);
  } else {
    errorDialog(usbdevice_modid);
  }
}

int dialogSteps() {
  int refresh = REFRESH_MODE_NONE;

  int msg_result = updateMessageDialog();
  int netcheck_result = updateNetCheckDialog();
  int ime_result = updateImeDialog();

  switch (getDialogStep()) {
    case DIALOG_STEP_ERROR:
    case DIALOG_STEP_INFO:
    case DIALOG_STEP_SYSTEM:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
          msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_CANCELED:
      refresh = REFRESH_MODE_NORMAL;
      setDialogStep(DIALOG_STEP_NONE);
      break;
      
    case DIALOG_STEP_DELETED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
          msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
        if (file_entry) {
          // Empty mark list if on marked entry
          if (fileListFindEntry(&mark_list, file_entry->name)) {
            fileListEmpty(&mark_list);
          }

          refresh = REFRESH_MODE_NORMAL;
        }
        
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_COMPRESSED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
          msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
        if (file_entry) {
          // Empty mark list if on marked entry
          if (fileListFindEntry(&mark_list, file_entry->name)) {
            fileListEmpty(&mark_list);
          }
          
          // Focus
          setFocusName(compress_name);
          
          refresh = REFRESH_MODE_SETFOCUS;
        }
        
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_COPIED:
    case DIALOG_STEP_MOVED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
          msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        // Empty mark list
        fileListEmpty(&mark_list);
        
        // Copy copy list to mark list
        FileListEntry *copy_entry = copy_list.head;
        
        int i;
        for (i = 0; i < copy_list.length; i++) {
          fileListAddEntry(&mark_list, fileListCopyEntry(copy_entry), SORT_NONE);

          // Next
          copy_entry = copy_entry->next;
        }
        
        // Focus
        setFocusName(copy_list.head->name);

        // Empty copy list when moved
        if (getDialogStep() == DIALOG_STEP_MOVED)
          fileListEmpty(&copy_list);
        
        // Umount and remove from clipboard after pasting
        if (pfs_mounted_path[0] &&
            !strstr(file_list.path, pfs_mounted_path) &&
             strstr(copy_list.path, pfs_mounted_path)) {
          pfsUmount();
          fileListEmpty(&copy_list);
        }

        refresh = REFRESH_MODE_SETFOCUS;
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_REFRESH_LIVEAREA_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[REFRESHING]);
        setDialogStep(DIALOG_STEP_REFRESHING);

        SceUID thid = sceKernelCreateThread("refresh_thread", (SceKernelThreadEntry)refresh_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, 0, NULL);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_REFRESH_LICENSE_DB_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[REFRESHING]);
        setDialogStep(DIALOG_STEP_REFRESHING);

        SceUID thid = sceKernelCreateThread("license_thread", (SceKernelThreadEntry)license_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, 0, NULL);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }

    case DIALOG_STEP_USB_ATTACH_WAIT:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        if (checkFileExist("sdstor0:uma-lp-act-entire")) {
          sceMsgDialogClose();
        }
      } else {
        if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
            msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
          setDialogStep(DIALOG_STEP_NONE);
          
          if (checkFileExist("sdstor0:uma-lp-act-entire")) {
            int res = vshIoMount(0xF00, NULL, 0, 0, 0, 0);
            if (res < 0)
              errorDialog(res);
            else
              infoDialog(language_container[UMA0_MOUNTED]);
            refresh = REFRESH_MODE_NORMAL;
          }
        }
      }
      
      break;
    }
    
    case DIALOG_STEP_FTP_WAIT:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        int state = 0;
        sceNetCtlInetGetState(&state);
        if (state == 3) {
          int res = ftpvita_init(vita_ip, &vita_port);
          if (res >= 0) {
            initFtp();
            sceMsgDialogClose();
          }
        }
      } else {
        if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
            msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
          setDialogStep(DIALOG_STEP_NONE);

          // Dialog
          if (ftpvita_is_initialized()) {
            initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_OK_CANCEL, language_container[FTP_SERVER], vita_ip, vita_port);
            setDialogStep(DIALOG_STEP_FTP);
          } else {
            powerUnlock();
          }
        }
      }
      
      break;
    }
    
    case DIALOG_STEP_FTP:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        powerUnlock();
        ftpvita_fini();
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_USB_WAIT:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        SceUdcdDeviceState state;
        sceUdcdGetDeviceState(&state);
        
        if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED) {
          sceMsgDialogClose();
        }
      } else {
        if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
            msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
          setDialogStep(DIALOG_STEP_NONE);

          SceUdcdDeviceState state;
          sceUdcdGetDeviceState(&state);
          
          if (state.cable & SCE_UDCD_STATUS_CABLE_CONNECTED) {
            initUsb();
          }
        }
      }
      
      break;
    }
    
    case DIALOG_STEP_USB:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        SceUdcdDeviceState state;
        sceUdcdGetDeviceState(&state);
        
        if (state.cable & SCE_UDCD_STATUS_CABLE_DISCONNECTED) {
          sceMsgDialogClose();
        }
      } else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        powerUnlock();
        stopUsb(usbdevice_modid);
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_PASTE:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        CopyArguments args;
        args.file_list = &file_list;
        args.copy_list = &copy_list;
        args.archive_path = archive_copy_path;
        args.copy_mode = copy_mode;

        setDialogStep(DIALOG_STEP_COPYING);

        SceUID thid = sceKernelCreateThread("copy_thread", (SceKernelThreadEntry)copy_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(CopyArguments), &args);
      }

      break;
    }
    
    case DIALOG_STEP_DELETE_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[DELETING]);
        setDialogStep(DIALOG_STEP_DELETE_CONFIRMED);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_DELETE_CONFIRMED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        DeleteArguments args;
        args.file_list = &file_list;
        args.mark_list = &mark_list;
        args.index = base_pos + rel_pos;

        setDialogStep(DIALOG_STEP_DELETING);

        SceUID thid = sceKernelCreateThread("delete_thread", (SceKernelThreadEntry)delete_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(DeleteArguments), &args);
      }

      break;
    }
    
    case DIALOG_STEP_EXPORT_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[EXPORTING]);
        setDialogStep(DIALOG_STEP_EXPORT_CONFIRMED);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_EXPORT_CONFIRMED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        ExportArguments args;
        args.file_list = &file_list;
        args.mark_list = &mark_list;
        args.index = base_pos + rel_pos;

        setDialogStep(DIALOG_STEP_EXPORTING);

        SceUID thid = sceKernelCreateThread("export_thread", (SceKernelThreadEntry)export_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(ExportArguments), &args);
      }

      break;
    }
    
    case DIALOG_STEP_RENAME:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *name = (char *)getImeDialogInputTextUTF8();
        if (name[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
          if (!file_entry) {
            setDialogStep(DIALOG_STEP_NONE);
            break;
          }
          
          char old_name[MAX_NAME_LENGTH];
          strcpy(old_name, file_entry->name);
          removeEndSlash(old_name);

          if (strcasecmp(old_name, name) == 0) { // No change
            setDialogStep(DIALOG_STEP_NONE);
          } else {
            char old_path[MAX_PATH_LENGTH];
            char new_path[MAX_PATH_LENGTH];

            snprintf(old_path, MAX_PATH_LENGTH, "%s%s", file_list.path, old_name);
            snprintf(new_path, MAX_PATH_LENGTH, "%s%s", file_list.path, name);

            int res = sceIoRename(old_path, new_path);
            if (res < 0) {
              errorDialog(res);
            } else {
              refresh = REFRESH_MODE_NORMAL;
              setDialogStep(DIALOG_STEP_NONE);
            }
          }
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }

    case DIALOG_STEP_NEW_FOLDER:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *name = (char *)getImeDialogInputTextUTF8();
        if (name[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          char path[MAX_PATH_LENGTH];
          snprintf(path, MAX_PATH_LENGTH, "%s%s", file_list.path, name);

          int res = sceIoMkdir(path, 0777);
          if (res < 0) {
            errorDialog(res);
          } else {
            // Focus
            char focus_name[MAX_NAME_LENGTH];
            strcpy(focus_name, name);
            addEndSlash(focus_name);
            setFocusName(focus_name);
            
            refresh = REFRESH_MODE_SETFOCUS;
            setDialogStep(DIALOG_STEP_NONE);
          }
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }

    case DIALOG_STEP_NEW_FILE:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *name = (char *)getImeDialogInputTextUTF8();
        if (name[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          char path[MAX_PATH_LENGTH];
          snprintf(path, MAX_PATH_LENGTH, "%s%s", file_list.path, name);

          SceUID fd = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT, 0777);
          if (fd < 0) {
            errorDialog(fd);
          } else {
            sceIoClose(fd);

            // Focus
            char focus_name[MAX_NAME_LENGTH];
            strcpy(focus_name, name);
            addEndSlash(focus_name);
            setFocusName(focus_name);

            refresh = REFRESH_MODE_SETFOCUS;
            setDialogStep(DIALOG_STEP_NONE);
            refreshFileList();
          }
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      break;
    }

    case DIALOG_STEP_COMPRESS_NAME:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *name = (char *)getImeDialogInputTextUTF8();
        if (name[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          strcpy(compress_name, name);

          initImeDialog(language_container[COMPRESSION_LEVEL], "6", 1, SCE_IME_TYPE_NUMBER, 0, 0);
          setDialogStep(DIALOG_STEP_COMPRESS_LEVEL);
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }

    case DIALOG_STEP_COMPRESS_LEVEL:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *level = (char *)getImeDialogInputTextUTF8();
        if (level[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          snprintf(cur_file, MAX_PATH_LENGTH, "%s%s", file_list.path, compress_name);

          CompressArguments args;
          args.file_list = &file_list;
          args.mark_list = &mark_list;
          args.index = base_pos + rel_pos;
          args.level = atoi(level);
          args.path = cur_file;

          initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[COMPRESSING]);
          setDialogStep(DIALOG_STEP_COMPRESSING);

          SceUID thid = sceKernelCreateThread("compress_thread", (SceKernelThreadEntry)compress_thread, 0x40, 0x100000, 0, 0, NULL);
          if (thid >= 0)
            sceKernelStartThread(thid, sizeof(CompressArguments), &args);
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_HASH_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        // Throw up the progress bar, enter hashing state
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[HASHING]);
        setDialogStep(DIALOG_STEP_HASH_CONFIRMED);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        // Quit
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_HASH_CONFIRMED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        // User has confirmed desire to hash, get requested file entry
        FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
        if (!file_entry) {
          setDialogStep(DIALOG_STEP_NONE);
          break;
        }
        
        // Place the full file path in cur_file
        snprintf(cur_file, MAX_PATH_LENGTH, "%s%s", file_list.path, file_entry->name);

        HashArguments args;
        args.file_path = cur_file;

        setDialogStep(DIALOG_STEP_HASHING);

        // Create a thread to run out actual sum
        SceUID thid = sceKernelCreateThread("hash_thread", (SceKernelThreadEntry)hash_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(HashArguments), &args);
      }

      break;
    }
    
    case DIALOG_STEP_INSTALL_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[INSTALLING]);
        setDialogStep(DIALOG_STEP_INSTALL_CONFIRMED);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_INSTALL_CONFIRMED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        InstallArguments args;

        if (install_list.length > 0) {
          FileListEntry *entry = install_list.head;
          snprintf(install_path, MAX_PATH_LENGTH, "%s%s", install_list.path, entry->name);
          args.file = install_path;

          // Focus
          setFocusOnFilename(entry->name);

          // Remove entry
          fileListRemoveEntry(&install_list, entry);
        } else {
          args.file = cur_file;
        }

        setDialogStep(DIALOG_STEP_INSTALLING);

        SceUID thid = sceKernelCreateThread("install_thread", (SceKernelThreadEntry)install_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(InstallArguments), &args);
      }

      break;
    }
    
    case DIALOG_STEP_INSTALL_CONFIRMED_QR:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        InstallArguments args;
        args.file = getLastDownloadQR();

        setDialogStep(DIALOG_STEP_INSTALLING);

        SceUID thid = sceKernelCreateThread("install_thread", (SceKernelThreadEntry)install_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, sizeof(InstallArguments), &args);
      }

      break;
    }
 
    case DIALOG_STEP_INSTALL_WARNING:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        setDialogStep(DIALOG_STEP_INSTALL_WARNING_AGREED);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_CANCELED);
      }

      break;
    }
    
    case DIALOG_STEP_INSTALLED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_NONE ||
          msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        if (install_list.length > 0) {
          initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[INSTALLING]);
          setDialogStep(DIALOG_STEP_INSTALL_CONFIRMED);
          break;
        }

        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_UPDATE_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[DOWNLOADING]);
        setDialogStep(DIALOG_STEP_DOWNLOADING);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }
    }
    
    case DIALOG_STEP_DOWNLOADED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[INSTALLING]);

        setDialogStep(DIALOG_STEP_EXTRACTING);

        SceUID thid = sceKernelCreateThread("update_extract_thread", (SceKernelThreadEntry)update_extract_thread, 0x40, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, 0, NULL);
      }

      break;
    }
    
    case DIALOG_STEP_SETTINGS_AGREEMENT:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        settingsAgree();
        setDialogStep(DIALOG_STEP_NONE);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        settingsDisagree();
        setDialogStep(DIALOG_STEP_NONE);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        settingsAgree();
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_SETTINGS_STRING:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *string = (char *)getImeDialogInputTextUTF8();
        if (string[0] != '\0') {
          strcpy((char *)getImeDialogInitialText(), string);
        }

        setDialogStep(DIALOG_STEP_NONE);
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_EXTRACTED:
    {
			removePath("ux0:patch/VitaTweakBox", NULL);
      launchAppByUriExit("VSUPDATER");
      setDialogStep(DIALOG_STEP_NONE);
      break;
    }
      
    case DIALOG_STEP_QR:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        setDialogStep(DIALOG_STEP_NONE);
        setScannedQR(0);
      } else if (scannedQR()) {
        setDialogStep(DIALOG_STEP_QR_DONE);
        sceMsgDialogClose();
        setScannedQR(0);
        stopQR();
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_DONE:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        setDialogStep(DIALOG_STEP_QR_WAITING);
        stopQR();
        SceUID thid = sceKernelCreateThread("qr_scan_thread", (SceKernelThreadEntry)qr_scan_thread, 0x10000100, 0x100000, 0, 0, NULL);
        if (thid >= 0)
          sceKernelStartThread(thid, 0, NULL);
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_WAITING:
    {
      break;
    }
    
    case DIALOG_STEP_QR_CONFIRM:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[DOWNLOADING]);
        setDialogStep(DIALOG_STEP_QR_DOWNLOADING);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_DOWNLOADED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_DOWNLOADED_VPK:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[INSTALLING]);
        setDialogStep(DIALOG_STEP_INSTALL_CONFIRMED_QR);
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_OPEN_WEBSITE:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        setDialogStep(DIALOG_STEP_NONE);
        sceAppMgrLaunchAppByUri(0xFFFFF, getLastQR());
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        setDialogStep(DIALOG_STEP_NONE);
      } else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        setDialogStep(DIALOG_STEP_NONE);
        sceAppMgrLaunchAppByUri(0xFFFFF, getLastQR());
      }
      
      break;
    }
    
    case DIALOG_STEP_QR_SHOW_CONTENTS:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ENTER_PASSWORD:
    {
      if (ime_result == IME_DIALOG_RESULT_FINISHED) {
        char *password = (char *)getImeDialogInputTextUTF8();
        if (password[0] == '\0') {
          setDialogStep(DIALOG_STEP_NONE);
        } else {
          // TODO: verify password
          archiveSetPassword(password);
          
          FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
          if (!file_entry) {
            setDialogStep(DIALOG_STEP_NONE);
            break;
          }
          
          setInArchive();
          setDirArchiveLevel();

          snprintf(archive_path, MAX_PATH_LENGTH, "%s%s", file_list.path, file_entry->name);

          strcat(file_list.path, file_entry->name);
          addEndSlash(file_list.path);

          dirLevelUp();
          
          refresh = REFRESH_MODE_NORMAL;
          setDialogStep(DIALOG_STEP_NONE);
        }
      } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
        setDialogStep(DIALOG_STEP_NONE);
      }

      break;
    }
    
    case DIALOG_STEP_ADHOC_SEND_NETCHECK:
    {
      if (netcheck_result == NETCHECK_DIALOG_RESULT_CONNECTED) {
        initAdhocDialog();
        setDialogStep(DIALOG_STEP_NONE);
      } else if (netcheck_result == NETCHECK_DIALOG_RESULT_NOT_CONNECTED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_SEND_WAITING:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        // Wait for a response, then close
        if (strcmp(adhocReceiveClientReponse(), "YES") == 0 ||
            strcmp(adhocReceiveClientReponse(), "NO") == 0) {
          sceMsgDialogClose();
        }
      } else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        if (strcmp(adhocReceiveClientReponse(), "YES") == 0) {
          SendArguments args;
          args.file_list = &file_list;
          args.mark_list = &mark_list;
          args.index = base_pos + rel_pos;

          initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[SENDING]);
          setDialogStep(DIALOG_STEP_ADHOC_SENDING);

          SceUID thid = sceKernelCreateThread("send_thread", (SceKernelThreadEntry)send_thread, 0x40, 0x100000, 0, 0, NULL);
          if (thid >= 0)
            sceKernelStartThread(thid, sizeof(SendArguments), &args);
        } else if (strcmp(adhocReceiveClientReponse(), "NO") == 0) {
          initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL, language_container[ADHOC_CLIENT_DECLINED]);
          setDialogStep(DIALOG_STEP_ADHOC_SEND_CLIENT_DECLINED);
        } else {
          // Return to select menu
          adhocCloseSockets();
          initAdhocDialog();
          setDialogStep(DIALOG_STEP_NONE);
        }
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_SEND_CLIENT_DECLINED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        // Return to select menu
        adhocCloseSockets();
        initAdhocDialog();
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_RECEIVE_NETCHECK:
    {
      if (netcheck_result == NETCHECK_DIALOG_RESULT_CONNECTED) {
        adhocWaitingForServerRequest();
        initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL, language_container[ADHOC_RECEIVE_SEARCHING_PSVITA]);
        setDialogStep(DIALOG_STEP_ADHOC_RECEIVE_SEARCHING);
      } else if (netcheck_result == NETCHECK_DIALOG_RESULT_NOT_CONNECTED) {
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_RECEIVE_SEARCHING:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_RUNNING) {
        // Wait for a request, then close
        if (adhocReceiveServerRequest() == 1) {
          sceMsgDialogClose();
        }
      } else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        // If the dialog is closed and we got a request, go to question state, otherwise end waiting
        if (adhocReceiveServerRequest() == 1) {
          initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[ADHOC_RECEIVE_QUESTION], adhocGetServerNickname());
          setDialogStep(DIALOG_STEP_ADHOC_RECEIVE_QUESTION);
        } else {
          adhocCloseSockets();
          sceNetCtlAdhocDisconnect();
          setDialogStep(DIALOG_STEP_NONE);
        }
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_RECEIVE_QUESTION:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
        int res = adhocSendServerResponse("YES");
        if (res < 0) {
          adhocCloseSockets();
          sceNetCtlAdhocDisconnect();
          errorDialog(res);
        } else {
          ReceiveArguments args;
          args.file_list = &file_list;
          args.mark_list = &mark_list;
          args.index = base_pos + rel_pos;

          initMessageDialog(MESSAGE_DIALOG_PROGRESS_BAR, language_container[RECEIVING]);
          setDialogStep(DIALOG_STEP_ADHOC_RECEIVING);

          SceUID thid = sceKernelCreateThread("receive_thread", (SceKernelThreadEntry)receive_thread, 0x40, 0x100000, 0, 0, NULL);
          if (thid >= 0)
            sceKernelStartThread(thid, sizeof(ReceiveArguments), &args);
        }
      } else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
        adhocSendServerResponse("NO"); // Do not check result
        
        // Go back to searching
        adhocCloseSockets();
        adhocWaitingForServerRequest();
        initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_CANCEL, language_container[ADHOC_RECEIVE_SEARCHING_PSVITA]);
        setDialogStep(DIALOG_STEP_ADHOC_RECEIVE_SEARCHING);
      }

      break;
    }
    
    case DIALOG_STEP_ADHOC_SENDED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_RECEIVED:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        refresh = REFRESH_MODE_NORMAL;
        setDialogStep(DIALOG_STEP_NONE);
      }
      
      break;
    }
    
    case DIALOG_STEP_ADHOC_SENDING:
    case DIALOG_STEP_ADHOC_RECEIVING:
    {
      if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
        // Alert sockets
        adhocAlertSockets();
      }
      
      break;
    }
	
	/////////////// BMK ////////////////
		case DIALOG_STEP_ENTER_ARCHIVE_BOOKS_PASSWORD:
		{
		  if (ime_result == IME_DIALOG_RESULT_FINISHED) {
			char *password = (char *)getImeDialogInputTextUTF8();
			if (password[0] == '\0') {
			  setDialogStep(DIALOG_STEP_NONE);
			} else {
			  // TODO: verify password
			  archiveSetPassword(password);
			  
			  /*FileListEntry *file_entry = fileListGetNthEntry(&file_list, base_pos + rel_pos);
			  if (!file_entry) {
				setDialogStep(DIALOG_STEP_NONE);
				break;
			  }*/
			  
			  /*setInArchive();
			  setDirArchiveLevel();
			  //archiveOK = 1;

			  snprintf(archive_path, MAX_PATH_LENGTH, "%s%s", file_list.path, file_entry->name);

			  strcat(file_list.path, file_entry->name);
			  addEndSlash(file_list.path);

			  dirLevelUp();
			  
			  refresh = REFRESH_MODE_NORMAL;
			  setDialogStep(DIALOG_STEP_NONE);*/
			}
		  } else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
			setDialogStep(DIALOG_STEP_NONE);
		  }

		  break;
		}
	
		case DIALOG_STEP_VITAIDENT_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				VitaidentAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				VitaidentDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				VitaidentAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		case DIALOG_STEP_FORECAST_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				ForeCastAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				ForeCastDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				ForeCastAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
					
		case DIALOG_STEP_FORECAST_ZIP:
		{
			if (ime_result == IME_DIALOG_RESULT_FINISHED) {
				char *name = (char *)getImeDialogInputTextUTF8();
				if (name[0] == '\0') {
				  setDialogStep(DIALOG_STEP_NONE);
				} else {
				    strcpy(zip, name);
					WriteFile("ux0:VitaTweakBox/tweaks/Forecast/zipCode.txt", zip, 12);
					downloadWeatherData();
					setDialogStep(DIALOG_STEP_NONE);
				  }
				  
			}else if (ime_result == IME_DIALOG_RESULT_CANCELED) {
				setDialogStep(DIALOG_STEP_NONE);
			}
			
			break;
		}
			
		case DIALOG_STEP_VITABACKUP_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				VitabackupAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				VitabackupDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				VitabackupAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_VITABACKUP_MENU_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				VitamenubackupAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				VitamenubackupDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				VitamenubackupAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_VITARESTORE_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				VitarestoreAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				VitarestoreDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				VitarestoreAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		/*case DIALOG_STEP_VITAOPTIONS_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				VitaoptionsAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				VitaoptionsDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				VitaoptionsAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}*/
			
		case DIALOG_STEP_BROWSER_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				BrowserAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				BrowserDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				BrowserAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_BOOK_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				bookAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				bookDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				bookAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		case DIALOG_STEP_DATABASE_AGREEMENT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				databaseAgree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				databaseDisagree();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_FINISHED) {
				databaseAgree();
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_DATABASE_UPDATE:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				sceIoRemove("ux0:/id.dat");
				DataBaserebootDevice();
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		case DIALOG_STEP_DATABASE_REBUILD:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				sceIoRemove("ur0:/shell/db/app.db");
				DataBaserebootDevice();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_DATABASE_SAVE_LAYOUT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[DATABASEREBUILDCONFIRMQUESTION2]);
				dialog_step = DIALOG_STEP_DATABASE_CONFIRME_LAYOUT;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		
		case DIALOG_STEP_DATABASE_CONFIRME_LAYOUT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				int ret;
				ret = manageDb('s');
				if (!ret) {
					infoDialog(language_container[EXPORT_ERROR]);
					initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[DATABASEREBUILDCONFIRMQUESTION]);
					dialog_step = DIALOG_STEP_DATABASE_REBUILD;
				}else{
				sceIoRemove("ur0:/shell/db/app.db");
				FILE* file_ptr = fopen(FILE_NAME, "w");
				fclose(file_ptr);
				DataBaserebootDevice();
				dialog_step = DIALOG_STEP_NONE;
				}
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[DATABASEREBUILDCONFIRMQUESTION]);
				dialog_step = DIALOG_STEP_DATABASE_REBUILD;
			}
			
			break;
		}
		
		case DIALOG_STEP_DATABASE_UPDATE_QUESTION:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[DATABASEUPDATECONFIRMQUESTION]);
				dialog_step = DIALOG_STEP_DATABASE_UPDATE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		case DIALOG_STEP_DATABASE_IMPORT_LAYOUT:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				int ret;
				ret = importLASett();
				
				switch (ret) {
					case 0: {
						infoDialog(language_container[IMPORT_ERROR]);
					}
						break;
					case 2: {
						infoDialog(language_container[LIVEAREA_SETTINGS]);
					}
						break;
					default: {
						DataBaserebootDevice();
					}
						break;
				}
				
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
			
		case DIALOG_STEP_DATABASE_LAYOUT_AFTERREBUILD:
		{
			if (msg_result == MESSAGE_DIALOG_RESULT_YES) {
				int ret;
				ret = importLASett();
				sceIoRemove(FILE_NAME);
				DataBaserebootDevice();
				dialog_step = DIALOG_STEP_NONE;
			} else if (msg_result == MESSAGE_DIALOG_RESULT_NO) {
				sceIoRemove(FILE_NAME);
				dialog_step = DIALOG_STEP_NONE;
			}
			
			break;
		}
		////////////////////////////////////
	
  }

  return refresh;
}

void ftpvita_PROM(ftpvita_client_info_t *client) {
  char cmd[64];
  char path[MAX_PATH_LENGTH];
  sscanf(client->recv_buffer, "%s %s", cmd, path);

  if (installPackage(path) == 0) {
    ftpvita_ext_client_send_ctrl_msg(client, "200 OK PROMOTING\r\n");
  } else {
    ftpvita_ext_client_send_ctrl_msg(client, "500 ERROR PROMOTING\r\n");
  }
}

int main(int argc, const char *argv[]) {  
  // Create mutex
  sceKernelCreateLwMutex(&dialog_mutex, "dialog_mutex", 2, 0, NULL);

  // Init VitaShell
  initVitaShell();

  // No custom config, in case they are damaged or unuseable
  readPad();
  if (current_pad[PAD_LTRIGGER])
    use_custom_config = 0;
  
  // Load stuff
  loadSettingsConfig();
  loadTheme();
  loadLanguage(language);

  // Init context menu width
  initContextMenuWidth();
  initTextContextMenuWidth();
  
  // Automatic network update
  if (!vitashell_config.disable_autoupdate) {
    SceUID thid = sceKernelCreateThread("network_update_thread", network_update_thread, 0x10000100, 0x100000, 0, 0, NULL);
    if (thid >= 0)
      sceKernelStartThread(thid, 0, NULL);
  }

  // show if user rebuild BDD with icon layout
  if (checkFileExist(FILE_NAME)){
	  initMessageDialog(SCE_MSG_DIALOG_BUTTON_TYPE_YESNO, language_container[DATABASELAYOUTAFTERREBUILD]);
	  setDialogStep (DIALOG_STEP_DATABASE_LAYOUT_AFTERREBUILD);	
  }
  
  // App Menu
  vtbMain();

  // Finish VitaShell
  finishVitaShell();
  
  return 0;
}
