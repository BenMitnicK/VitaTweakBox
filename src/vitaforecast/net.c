#include "forecast.h"
#include "net.h"
#include "../utils.h"
#include "../main.h"

static char patch[MAX_PATH_LENGTH];

void download(const char *url, const char *dest) 
{
	snprintf(patch, MAX_PATH_LENGTH, "\n\nDownloading %s to %s\n", url, dest);
	//pgf_draw_text(40, 120, RGBA8(0, 0, 0, 255), 1.0f, patch);
	
	int tpl = sceHttpCreateTemplate("Weather Data", 1, 1);
	
	snprintf(patch, MAX_PATH_LENGTH, "0x%08X sceHttpCreateTemplate\n", tpl);
	//pgf_draw_text(40, 140, RGBA8(0, 0, 0, 255), 1.0f, patch);

	// set url on the template
	int conn = sceHttpCreateConnectionWithURL(tpl, url, 0);
	snprintf(patch, MAX_PATH_LENGTH, "0x%08X sceHttpCreateConnectionWithURL\n", conn);
	//pgf_draw_text(40, 160, RGBA8(0, 0, 0, 255), 1.0f, patch);

	// create the request with the correct method
	int request = sceHttpCreateRequestWithURL(conn, SCE_HTTP_METHOD_GET, url, 0);
	snprintf(patch, MAX_PATH_LENGTH, "0x%08X sceHttpCreateRequestWithURL\n", request);
	//pgf_draw_text(40, 180, RGBA8(0, 0, 0, 255), 1.0f, patch);

	// send the actual request. Second parameter would be POST data, third would be length of it.
	int handle = sceHttpSendRequest(request, NULL, 0);
	snprintf(patch, MAX_PATH_LENGTH, "0x%08X sceHttpSendRequest\n", handle);
	//pgf_draw_text(40, 200, RGBA8(0, 0, 0, 255), 1.0f, patch);

	// open destination file
	int fh = sceIoOpen(dest, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	snprintf(patch, MAX_PATH_LENGTH, "0x%08X sceIoOpen\n", fh);
	//pgf_draw_text(40, 220, RGBA8(0, 0, 0, 255), 1.0f, patch);

	// create buffer and counter for read bytes.
	unsigned char data[16*1024];
	int read = 0;

	// read data until finished
	while ((read = sceHttpReadData(request, &data, sizeof(data))) > 0) {
		snprintf(patch, MAX_PATH_LENGTH, "read %d bytes\n", read);
		//pgf_draw_text(240, 120, RGBA8(0, 0, 0, 255), 1.0f, patch);

		// writing the count of read bytes from the data buffer to the file
		int write = sceIoWrite(fh, data, read);
		snprintf(patch, MAX_PATH_LENGTH, "wrote %d bytes\n", write);
		//pgf_draw_text(260, 120, RGBA8(0, 0, 0, 255), 1.0f, patch);
	}

	// close file
	sceIoClose(fh);
	//pgf_draw_text(40, 280, RGBA8(0, 0, 0, 255), 1.0f, "sceIoClose\n");
}

char * fc_getIP() //local ip
{
	static char address[16];

	SceNetCtlInfo info;
	if (sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info) < 0) 
	{
		strcpy(address, "-");
	}
	else 
	{
		strcpy(address, info.ip_address);
	}
	
	return address;
}