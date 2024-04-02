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

#ifndef __BROWSER_H__
#define __BROWSER_H__

#define MAX_DIR_LEVELS 128

#define HOME_PATH "home"
#define DIR_UP ".."

enum BrowserAgreement {
	BROWSER_AGREEMENT_NONE,
	BROWSER_AGREEMENT_AGREE,
	BROWSER_AGREEMENT_DISAGREE,
};

enum BrowserOptionType {
	BROWSER_OPTION_TYPE_BOOLEAN,
	BROWSER_OPTION_TYPE_INTEGER,
	BROWSER_OPTION_TYPE_STRING,
	BROWSER_OPTION_TYPE_CALLBACK,
	BROWSER_OPTION_TYPE_NOTHING,
};

enum BrowserMenuStatus {
	BROWSER_MENU_CLOSED,
	BROWSER_MENU_CLOSING,
	BROWSER_MENU_OPENED,
	BROWSER_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
} BrowserMenu;

void initBrowserMenu();
void openBrowserMenu();
void closeBrowserMenu();
int getBrowserMenuStatus();
void drawBrowserMenu();
void BrowserMenuCtrl();

void BrowserAgree();
void BrowserDisagree();

extern FileList file_list, mark_list, copy_list, install_list;

extern char cur_file[MAX_PATH_LENGTH];
extern char archive_copy_path[MAX_PATH_LENGTH];
extern char archive_path[MAX_PATH_LENGTH];

extern int base_pos, rel_pos;
extern int sort_mode, copy_mode;

extern int last_set_sort_mode;

// minimum time to pass before shortcutting to recent files/ bookmarks via L/R keys
extern SceInt64 time_last_recent_files, time_last_bookmarks;
#define THRESHOLD_LAST_PAD_RECENT_FILES_WAIT 1000000
#define THRESHOLD_LAST_PAD_BOOKMARKS_WAIT 1000000

void dirLevelUp();

void setDirArchiveLevel();
void setInArchive();
int isInArchive();

void setFocusName(const char *name);
void setFocusOnFilename(const char *name);

void refreshMarkList();
void refreshCopyList();
extern char focus_name[MAX_NAME_LENGTH];

int refreshFileList();

int jump_to_directory_track_current_path(char *path);

void drawScrollBar(int pos, int n);
void drawShellInfo(const char *path);

//int browserMain();

#endif
