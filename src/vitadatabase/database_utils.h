#pragma once

#include "database_file.h"

#define APPDB    "ur0:shell/db/app.db"
#define ICO_PATH "ux0:VitaTweakBox/Tweaks/database/icons_pos.txt"
#define PID_PATH "ux0:VitaTweakBox/Tweaks/database/pages_pos.txt"
#define LOG_PATH "ux0:VitaTweakBox/Tweaks/database/logs"
#define ADB_PATH "ux0:VitaTweakBox/Tweaks/database/app_restored.db"
#define FILE_NAME "ux0:VitaTweakBox/Tweaks/database/on"

int init();
int manageDb(char cmd);
int importLASett();
