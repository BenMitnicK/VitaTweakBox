#include "../vitabackup.h"

const char * configFile = "storage_location = %d\n";
SceBool storage_location;
	
SceInt Options_SaveConfig(SceBool storage_location)
{
	SceInt ret = 0;
	
	char *config_path = (char *)malloc(32);
	snprintf(config_path, 32, "ur0:/data/VitaBackup/config.cfg");

	char *buf = (char *)malloc(128);
	SceInt len = snprintf(buf, 128, configFile, storage_location);
	
	if (R_FAILED(ret = FS_WriteFile(config_path, buf, len)))
	{
		free(config_path);
		free(buf);
		return ret;
	}
	
	free(config_path);
	free(buf);
	return 0;
}

SceInt Options_LoadConfig(SceVoid)
{
	SceInt ret = 0;	

	char *config_path = (char *)malloc(32);
	snprintf(config_path, 32, "ur0:/data/VitaBackup/config.cfg");

	if (!(FS_FileExists(config_path)))
	{
		storage_location = SCE_FALSE; // 0(FALSE) = ux0: and 1(TRUE) = ur0:

		Options_SaveConfig(storage_location);
	}

	char *buf = (char *)malloc(128);

	if (R_FAILED(ret = FS_ReadFile(config_path, buf, 128)))
	{
		free(config_path);
		free(buf);
		return ret;
	}

	sscanf(buf, configFile, &storage_location);

	free(config_path);
	free(buf);
	return 0;
}
