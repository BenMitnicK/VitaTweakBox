#ifndef __MENU_OPTIONS_H__
#define __MENU_OPTIONS_H__

extern SceBool storage_location;

SceInt Options_LoadConfig(SceVoid);
SceInt Options_SaveConfig(SceBool storage_location);

#endif
