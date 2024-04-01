#include "../vitabackup.h"
#include "../../language.h"

static mtar_t tar;

static SceInt MicrotarWrite_AddFileToTar(char *src)
{
	SceInt ret = 0;

	SceInt chunksize = (512 * 1024); // Chunk size
	char *buffer = (char *)malloc(chunksize); // Reading buffer

	size_t totalWritten = 0, totalRead = 0; 

	SceOff size = FS_GetFileSize(src); // Get input file size

	SceInt in = 0;

	// Opened file for reading
	if (R_SUCCEEDED(in = sceIoOpen(src, SCE_O_RDONLY, 0))) // Open file for reading
	{
		size_t bytesRead = 0; // Read byte count
		mtar_write_file_header(&tar, src, size);

		// Copy loop (512KB at a time)
		while((bytesRead = sceIoRead(in, buffer, chunksize)) > 0)
		{
			totalRead += bytesRead; // Accumulate read data
			totalWritten += mtar_write_data(&tar, buffer, bytesRead); // Write data
		
			ProgressBar_DisplayProgress(language_container[BACKUP_PROGRESS], Utils_Basename(src), totalRead, size);
		}

		if (totalRead != totalWritten) // Insufficient copy
			ret = -3;
			
		if (R_FAILED(ret = sceIoClose(in)))
		{
			DEBUG_PRINT("sceIoClose(in) failed: 0x%lx\n\n", ret);
			free(buffer);
			return ret;
		}
	}
	else
	{
		DEBUG_PRINT("in = sceIoOpen(src, SCE_O_RDONLY, 0) failed: 0x%lx\n\n", in);
		free(buffer);
		return in;
	}
	
	free(buffer); // Free memory
	return ret; // Return result
}

static SceInt MicrotarWrite_AddFileToTarRec(char *src)
{
	SceInt dir = 0;
	
	if (R_SUCCEEDED(dir = sceIoDopen(src)))
	{
		mtar_write_dir_header(&tar, src);
		SceInt ret = 1;

		while (ret > 0)
		{
			SceIoDirent entry;
			memset(&entry, 0, sizeof(entry));

			if (R_SUCCEEDED(ret = sceIoDread(dir, &entry)))
			{
				if (strlen(entry.d_name) > 0)
				{
					// Calculate Buffer Size
					int insize = strlen(src) + strlen(entry.d_name) + 2;

					char * inbuffer = (char *)malloc(insize);

					// Puzzle Input Path
					strcpy(inbuffer, src);
					inbuffer[strlen(inbuffer) + 1] = 0;
					inbuffer[strlen(inbuffer)] = '/';
					strcpy(inbuffer + strlen(inbuffer), entry.d_name);

					// Another Folder
					if (SCE_S_ISDIR(entry.d_stat.st_mode))
						MicrotarWrite_AddFileToTarRec(inbuffer); // Copy Folder (via recursion)

					// Simple File
					else 
						MicrotarWrite_AddFileToTar(inbuffer);

					// Free Buffer
					free(inbuffer);
				}
			}
			else
				return ret;
		}

		if (R_FAILED(ret = sceIoDclose(dir)))
		{
			DEBUG_PRINT("ret = sceIoDclose(dir) failed: 0x%lx\n\n", ret);
			return ret;
		}
	}
	else
	{
		DEBUG_PRINT("dir = sceIoDopen(src) failed: 0x%lx\n\n", dir);
		return dir;
	}

	return 0;
}

SceInt MicrotarWrite_AddToTar(char *src)
{
	SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);

	char *path = (char *)malloc(128);
	char *dateStr = (char *)malloc(24);
	Utils_GetDateString(dateStr, 0, time, SCE_FALSE);
	if(vitashell_config.backup_storage){
		snprintf(path, 128, "ur0:data/VitaBackup/backups/%s-%s.tar", Utils_RemoveExt(Utils_Basename(src)), dateStr);
	}else{
		snprintf(path, 128, "ux0:VitaTweakBox/tweaks/Vitabackup/backups/%s-%s.tar", Utils_RemoveExt(Utils_Basename(src)), dateStr);
	}
	if (FS_FileExists(path))
		FS_RemoveFile(path); // Delete output file (if existing)

	/* Open archive for writing */
	mtar_open(&tar, path, "w");

    SceIoStat stat;
	SceInt ret = 0;

	if (R_FAILED(ret = sceIoGetstat(src, &stat)))
	{
		free(path);
		free(dateStr);
		return ret;
	}

	if (SCE_S_ISDIR(stat.st_mode))
		MicrotarWrite_AddFileToTarRec(src);
	else 
		MicrotarWrite_AddFileToTar(src);

	free(path);
	free(dateStr);
	mtar_finalize(&tar); // Finalize archive
	mtar_close(&tar); // Close archive
	
	return 0;
}