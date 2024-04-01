#include "../vitabackup.h"
#include "../../language.h"
#include "../../io_process.h"
//#include "archive.h"
#include "../../message_dialog.h"
#include "../../uncommon_dialog.h"
#include "../../utils.h"

static mtar_t tar;
static SceOff tarSize;

static SceInt MicrotarRead_ExtractFileFromTarRec(char *dst)
{
	SceInt ret = 0;
	mtar_header_t header;

	// Read Success
	while ((mtar_read_header(&tar, &header)) != MTAR_ENULLRECORD)
	{
		if (header.type == MTAR_TDIR)
		{
			//DEBUG_PRINT("Dir name: %s\npos: %llu\nremaining_data: %llu\n\n", header.name, tar.pos, tar.remaining_data);
			FS_RecursiveMakeDir(header.name);
		}
		else
		{
			char *data = calloc(1, header.size + 1);
			if (R_FAILED(ret = mtar_read_data(&tar, data, header.size)))
			{
				//DEBUG_PRINT("mtar_read_data failed: 0x%lx\n\n", ret);
				return ret;
			}

			//DEBUG_PRINT("File name: %s\nFile size: %d\npos: %llu\nremaining_data: %llu\n\n", header.name, header.size, tar.pos, tar.remaining_data);
			ProgressBar_DisplayProgress(language_container[RESTORE_PROGRESS], Utils_Basename(header.name), tar.pos, tarSize);
			FS_WriteFile(header.name, data, header.size + 1);
			free(data);
		}

		mtar_next(&tar);
	}
		//infoDialog("Done!");
	return 0;
}

SceInt MicrotarRead_ExtractTar(char *src, char *dst)
{
	tarSize = FS_GetFileSize(src); // Get input file size

	/* Open archive for writing */
	mtar_open(&tar, src, "r");

	MicrotarRead_ExtractFileFromTarRec(dst);

	mtar_finalize(&tar); // Finalize archive
	mtar_close(&tar); // Close archive
	
	return 0;
}