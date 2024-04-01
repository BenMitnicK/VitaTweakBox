#include "vitaident.h"

char *Net_GetMacAddr(SceVoid)
{	
	SceNetEtherAddr mac;
	static char macAddress[0x12];
	
	if (R_SUCCEEDED(sceNetGetMacAddress(&mac, 0)))
		snprintf(macAddress, 0x12, "%02X:%02X:%02X:%02X:%02X:%02X", mac.data[0], mac.data[1], mac.data[2], mac.data[3], mac.data[4], mac.data[5]);

	return macAddress;
}

char *Net_GetIPAddr(SceVoid)
{
	SceNetCtlInfo info;
	static char address[0x11];
	
	if (R_SUCCEEDED(sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info)))
		snprintf(address, 0x11, info.ip_address);
	
	return address;
}
