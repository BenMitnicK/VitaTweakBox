#include "../main.h"
#include "../config.h"
#include "../init.h"
#include "../theme.h"
#include "../language.h"
#include "../message_dialog.h"
#include "../ime_dialog.h"
#include "../utils.h"
#include "vitaident.h"
#include "../touch.h"

#define MAX_ITEMS   7

static char patch[MAX_PATH_LENGTH];
static float width;

static int n_Vitaident_entries = 0;
static VitaidentMenu Vitaident_menu;

static int selection = 0;
static int item_height = 0;

void initVitaidentMenu() {
	memset(&Vitaident_menu, 0, sizeof(VitaidentMenu));
	Vitaident_menu.status = VITAIDENT_MENU_CLOSED;
	n_Vitaident_entries = 1;
}

void openVitaidentMenu() {
	Vitaident_menu.status = VITAIDENT_MENU_OPENING;
}

void closeVitaidentMenu() {
	Vitaident_menu.status = VITAIDENT_MENU_CLOSING;
}

int getVitaidentMenuStatus() {
	return Vitaident_menu.status;
}

void nameWidth(char *name){
	width = vita2d_pgf_text_width(font, 1, name);
}

static char *devices[] = 
{
	"ur0:",
	"ux0:",
	"imc0:",
	"uma0:",
};

static SceVoid Menu_Kernel(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "Kernel Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_KERNEL_COLOR, "Kernel Menu");
	
	pgf_draw_text(320, 160+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "Firmware version:");
	nameWidth("Firmware version:");
	pgf_draw_text(320 + width + 10, 160+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetFirmwareVersion(SCE_FALSE));
	
	pgf_draw_text(320, 200+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "System version:");
	nameWidth("System version:");
	pgf_draw_text(320 + width + 5, 200+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetFirmwareVersion(SCE_TRUE));
	
	snprintf(patch, MAX_PATH_LENGTH, "%s  %s", Kernel_GetDeviceModel(), vshSysconHasWWAN()? "3G" : "WiFi");
	pgf_draw_text(320, 240+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "Model:");
	nameWidth("Model:");
	pgf_draw_text(320 + width + 5, 240+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, patch);
	
	pgf_draw_text(320, 280+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "Unit:");
	nameWidth("Unit:");
	pgf_draw_text(320 + width + 5, 280+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetDeviceUnit());
	
	pgf_draw_text(320, 320+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "Motherboard:");
	nameWidth("Motherboard:");
	pgf_draw_text(320 + width + 5, 320+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetDeviceBoard());
	
	pgf_draw_text(320, 360+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "Console ID:");
	nameWidth("Console ID:");
	pgf_draw_text(320 + width + 5, 360+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetCID()); //Thanks Major_Tom
	
	pgf_draw_text(320, 400+slide_y, VITAIDENT_KERNEL_NAME_COLOR, "PSID:");
	nameWidth("PSID:");
	pgf_draw_text(320 + width + 5, 400+slide_y, VITAIDENT_KERNEL_ITEM_COLOR, Kernel_GetPSID()); //Thanks SMOKE
	
}

static SceVoid Menu_System(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "System Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_SYSTEM_COLOR, "System Menu");
	
	pgf_draw_text(320, 180+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "Language:");
	nameWidth("Language:");
	pgf_draw_text(320 + width + 5, 180+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, App_GetLanguage());
	
	pgf_draw_text(320, 220+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "MAC address:");
	nameWidth("MAC address:");
	pgf_draw_text(320 + width + 5, 220+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, Net_GetMacAddr());
	
	snprintf(patch, MAX_PATH_LENGTH, "%ld MHz\n", Power_GetClockFrequency(clockFrequencyType_cpu));
	pgf_draw_text(320, 260+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "ARM clock frequency:");
	nameWidth("ARM clock frequency:");
	pgf_draw_text(320 + width + 5, 260+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, patch);
	
	snprintf(patch, MAX_PATH_LENGTH, "%ld MHz\n", Power_GetClockFrequency(clockFrequencyType_bus));
	pgf_draw_text(320, 300+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "BUS clock frequency:");
	nameWidth("BUS clock frequency:");
	pgf_draw_text(320 + width + 5, 300+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, patch);
	
	snprintf(patch, MAX_PATH_LENGTH, "%ld MHz\n\n", Power_GetClockFrequency(clockFrequencyType_gpu));
	pgf_draw_text(320, 340+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "GPU clock frequency:");
	nameWidth("GPU clock frequency:");
	pgf_draw_text(320 + width + 5, 340+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, patch);
	
	snprintf(patch, MAX_PATH_LENGTH, "%ld MHz\n\n", Power_GetClockFrequency(clockFrequencyType_gpuXbar));
	pgf_draw_text(320, 380+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "GPU Xbar clock frequency:");
	nameWidth("GPU Xbar clock frequency:");
	pgf_draw_text(320 + width + 5, 380+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, patch);
	
}

static SceVoid Menu_Battery(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
    int batteryLifeTime = scePowerGetBatteryLifeTime();

	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "Battery Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_BATTERY_COLOR, "Battery Menu");
	
	/*snprintf(patch, MAX_PATH_LENGTH, "%s (%s)", Power_GetBatteryPercentage(), Power_GetBatteryStatus());
	pgf_draw_text(320, 190, VITAIDENT_BATTERY_NAME_COLOR, "Battery percentage: ");
	nameWidth("Battery percentage:");
	pgf_draw_text(320 + width + 5+slide_x, 190, VITAIDENT_BATTERY_ITEM_COLOR, patch);*/
	
	pgf_draw_text(320, 200+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "Battery capacity:");
	nameWidth("Battery capacity:");
	pgf_draw_text(320 + width + 5, 200+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, Power_GetBatteryCapacity());
	pgf_draw_text(320 + width + 120, 200+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "(remaining:");
	pgf_draw_text(320 + width + 230, 200+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, Power_GetBatteryStatus());
	pgf_draw_text(320 + width + 358, 200+slide_y, VITAIDENT_BATTERY_NAME_COLOR, ")");
	
	snprintf(patch, MAX_PATH_LENGTH, "%02dh %02dm", batteryLifeTime/60, batteryLifeTime-(batteryLifeTime/60*60));
	pgf_draw_text(320, 240+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "Battery life time:");
	nameWidth("Battery life time:");
	pgf_draw_text(320 + width + 5, 240+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, patch);
	pgf_draw_text(320 + width + 105, 240+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "(SOH:");
	pgf_draw_text(320 + width + 165, 240+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, Power_GetBatterySOH());
	pgf_draw_text(320 + width + 213, 240+slide_y, VITAIDENT_BATTERY_NAME_COLOR, ")");
	
	snprintf(patch, MAX_PATH_LENGTH, "%s C", Power_GetBatteryTemp(0));
	pgf_draw_text(320, 280+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "Battery temperature:");
	nameWidth("Battery temperature:");
	pgf_draw_text(320 + width + 5, 280+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, patch);
	pgf_draw_text(320 + width + 80, 280+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "(");
	snprintf(patch, MAX_PATH_LENGTH, "%s F", Power_GetBatteryTemp(1));
	pgf_draw_text(320 + width + 90, 280+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, patch);
	pgf_draw_text(320 + width + 157, 280+slide_y, VITAIDENT_BATTERY_NAME_COLOR, ")");
	
	snprintf(patch, MAX_PATH_LENGTH, "%s V", Power_GetBatteryVoltage());
	pgf_draw_text(320, 320+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "Battery voltage:");
	nameWidth("Battery voltage:");
	pgf_draw_text(320 + width + 5, 320+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, patch);
	pgf_draw_text(320 + width + 65, 320+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "(cycle count:");
	pgf_draw_text(320 + width + 193, 320+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, Power_GetBatteryCycleCount());
	pgf_draw_text(320 + width + 238, 320+slide_y, VITAIDENT_BATTERY_NAME_COLOR, ")");
	
	snprintf(patch, MAX_PATH_LENGTH, "%s", Power_GetUdcdCableState());
	pgf_draw_text(320, 360+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "Udcd state:");
	nameWidth("Udcd state:");
	pgf_draw_text(320 + width + 5, 360+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, patch);
	pgf_draw_text(320 + width + 205, 360+slide_y, VITAIDENT_BATTERY_NAME_COLOR, "(");
	pgf_draw_text(320 + width + 215, 360+slide_y, VITAIDENT_BATTERY_ITEM_COLOR, Power_GetUsbChargingState());
	pgf_draw_text(320 + width + 437, 360+slide_y, VITAIDENT_BATTERY_NAME_COLOR, ")");
	
}

static SceVoid Menu_Storage(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "Storage Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_SYSTEM_COLOR, "Storage Menu");
	
	vita2d_draw_texture(drive_image, 320, 64+slide_y);
	vita2d_draw_rectangle(450, 146+slide_y, 430, 16, VITAIDENT_STORAGE_BORDER_COLOR);
	vita2d_draw_rectangle(452, 148+slide_y, 426, 12, VITAIDENT_STORAGE_INSIDE_COLOR);
	vita2d_draw_rectangle(452, 148+slide_y, (((double)App_GetUsedCapacity(devices[0]) / (double)App_GetTotalCapacity(devices[0])) * 426.00), 12, VITAIDENT_STORAGE_BAR_COLOR);
	pgf_draw_text(450, 64+slide_y, VITAIDENT_STORAGE_DEVICE_COLOR, devices[0]);
	
	pgf_draw_text(450, 89+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Free size:");
	nameWidth("Free size:");
	pgf_draw_text(450 + width + 5, 89+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[0], 1));
	
	pgf_draw_text(450, 114+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Max size:");
	nameWidth("Max size:");
	pgf_draw_text(450 + width + 5, 114+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[0], 0));
    
	if (vshRemovableMemoryGetCardInsertState()) // if mem card is inserted
	{
		vita2d_draw_texture(drive_image, 320, 184+slide_y);
		vita2d_draw_rectangle(450, 266+slide_y, 430, 16, VITAIDENT_STORAGE_BORDER_COLOR);
		vita2d_draw_rectangle(452, 268+slide_y, 426, 12, VITAIDENT_STORAGE_INSIDE_COLOR);
		vita2d_draw_rectangle(452, 268+slide_y, (((double)App_GetUsedCapacity(devices[1]) / (double)App_GetTotalCapacity(devices[1])) * 426.00), 12, VITAIDENT_STORAGE_BAR_COLOR);
		pgf_draw_text(450, 184+slide_y, VITAIDENT_STORAGE_DEVICE_COLOR, devices[1]);
		
		pgf_draw_text(450, 209+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Free size:");
		nameWidth("Free size:");
		pgf_draw_text(450 + width + 5, 209+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[1], 1));
		
		pgf_draw_text(450, 234+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Max size:");
		nameWidth("Max size:");
		pgf_draw_text(450 + width + 5, 234+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[1], 0));
	}
	
	else if ((!vshRemovableMemoryGetCardInsertState()) || (isVTE1000))
	{
		vita2d_draw_texture(drive_image, 320, 184+slide_y);
		vita2d_draw_rectangle(450, 266+slide_y, 430, 16, VITAIDENT_STORAGE_BORDER_COLOR);
		vita2d_draw_rectangle(452, 268+slide_y, 426, 12, VITAIDENT_STORAGE_INSIDE_COLOR);
		vita2d_draw_rectangle(452, 268+slide_y, (((double)App_GetUsedCapacity(devices[2]) / (double)App_GetTotalCapacity(devices[2])) * 426.00), 12, VITAIDENT_STORAGE_BAR_COLOR);
		pgf_draw_text(450, 184+slide_y, VITAIDENT_STORAGE_DEVICE_COLOR, devices[2]);
		
		pgf_draw_text(450, 209+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Free size:");
		nameWidth("Free size:");
		pgf_draw_text(450 + width + 5, 209+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[2], 1));
		
		pgf_draw_text(450, 234+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Max size:");
		nameWidth("Max size:");
		pgf_draw_text(450 + width + 5, 234+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[2], 0));
	}
	
	if (App_GetTotalCapacity(devices[3]))
	{
		vita2d_draw_texture(drive_image, 320, 304+slide_y);
		vita2d_draw_rectangle(450, 386+slide_y, 430, 16, VITAIDENT_STORAGE_BORDER_COLOR);
		vita2d_draw_rectangle(452, 388+slide_y, 426, 12, VITAIDENT_STORAGE_INSIDE_COLOR);
		vita2d_draw_rectangle(452, 388+slide_y, (((double)App_GetUsedCapacity(devices[3]) / (double)App_GetTotalCapacity(devices[3])) * 426.00), 12, VITAIDENT_STORAGE_BAR_COLOR);
		pgf_draw_text(450, 304+slide_y, VITAIDENT_STORAGE_DEVICE_COLOR, devices[3]);
		
		pgf_draw_text(450, 329+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Free size:");
		nameWidth("Free size:");
		pgf_draw_text(450 + width + 5, 329+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[3], 1));
		
		pgf_draw_text(450, 354+slide_y, VITAIDENT_STORAGE_NAME_COLOR, "Max size:");
		nameWidth("Max size:");
		pgf_draw_text(450 + width + 5, 354+slide_y, VITAIDENT_STORAGE_ITEM_COLOR, App_GetStorageInfo(devices[3], 0));
	}
}

static SceInt wifiPage = 0;

static SceVoid Menu_WiFi(SceVoid)
{			
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "WiFi Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_PSN_COLOR, "WiFi Menu");
	
	switch(wifiPage)
	{
		case 0:
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(316, 56+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 58+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 60+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 1:");

				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 85+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 85+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 110+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 110+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/01/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/01/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(316, 154+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 156+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 158+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 2:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 183+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 183+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 208+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 208+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/02/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/02/WIFI/", "wpa_key"));                
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(316, 252+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 254+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 256+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 3:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 281+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 281+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 306+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 306+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/03/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/03/WIFI/", "wpa_key"));
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(316, 350+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 352+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 354+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 4:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 379+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 379+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 404+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 404+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/04/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/04/WIFI/", "wpa_key"));                
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "ssid"), "") != 0)
			{
				vita2d_draw_rectangle(316, 448+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 450+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 452+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 5:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 477+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 477+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 502+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 502+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/05/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/05/WIFI/", "wpa_key"));               
			}
			break;
			
		case 1:
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0)
			{
                vita2d_draw_rectangle(316, 56+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 58+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 60+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 6:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 85+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 85+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 110+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 110+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/06/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "wpa_key"));               
            }
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "ssid"), "") != 0)
			{
                vita2d_draw_rectangle(316, 154+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 156+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 158+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 7:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 183+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 183+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 208+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 208+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/07/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/07/WIFI/", "wpa_key"));                
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "ssid"), "") != 0)
			{
                vita2d_draw_rectangle(316, 252+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 254+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 256+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 8:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 281+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 281+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 306+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 306+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/08/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/08/WIFI/", "wpa_key"));                
            }
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "ssid"), "") != 0)
			{
                vita2d_draw_rectangle(316, 350+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 352+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 354+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 9:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 379+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 379+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 404+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 404+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/09/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/09/WIFI/", "wpa_key"));                
			}
	
			if (strcmp(RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "ssid"), "") != 0)
			{
                vita2d_draw_rectangle(316, 448+slide_y, 600, 80, VITAIDENT_WIFI_BORDER_COLOR);
				vita2d_draw_rectangle(318, 450+slide_y, 596, 76, VITAIDENT_WIFI_INSIDE_COLOR);
		
				pgf_draw_text(320, 452+slide_y, VITAIDENT_WIFI_PROFILE_COLOR, "Profile 10:");
				
				snprintf(patch, MAX_PATH_LENGTH, "%s %s", RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "ssid"), 
					RegMgr_GetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? "(WEP)" : "(WPA)");
				pgf_draw_text(320, 477+slide_y, VITAIDENT_WIFI_NAME_COLOR, "SSID:");
				nameWidth("SSID:");
				pgf_draw_text(320 + width + 5, 477+slide_y, VITAIDENT_WIFI_ITEM_COLOR, patch);
				
				pgf_draw_text(320, 502+slide_y, VITAIDENT_WIFI_NAME_COLOR, "Password:");
				nameWidth("Password:");
				pgf_draw_text(320 + width + 5, 502+slide_y, VITAIDENT_WIFI_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/10/WIFI/", "wifi_security") == 1? 
					RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "wep_key") : RegMgr_GetStr("/CONFIG/NET/10/WIFI/", "wpa_key"));                
			}
			break;
	}
}

static SceVoid Menu_Misc(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "Misc Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_MISC_COLOR, "Misc Menu");
	
	pgf_draw_text(320, 210+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "Username:");
	nameWidth("Username:");
	snprintf(patch, MAX_PATH_LENGTH, "%s", App_GetUser());
	pgf_draw_text(320 + width + 5, 210+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, patch);
	
	pgf_draw_text(320, 250+slide_y, VITAIDENT_SYSTEM_NAME_COLOR, "IP address:");
	nameWidth("IP address:");
	pgf_draw_text(320 + width + 5, 250+slide_y, VITAIDENT_SYSTEM_ITEM_COLOR, Net_GetIPAddr());
	
	pgf_draw_text(320, 290+slide_y, VITAIDENT_MISC_NAME_COLOR, "Enter button:");
	nameWidth("Enter button:");
	pgf_draw_text(320 + width + 5, 290+slide_y, VITAIDENT_MISC_ITEM_COLOR, App_GetEnterButton()? "cross (X)" : "circle (O)");
	
	SceInt fw = 0;
	if (R_SUCCEEDED(fw = sceCompatGetPspSystemSoftwareVersion()))
	snprintf(patch, MAX_PATH_LENGTH, "%ld.%.2ld", fw / 100, fw % 100);
	pgf_draw_text(320, 330+slide_y, VITAIDENT_MISC_NAME_COLOR, "PSP firmware version:");
	nameWidth("PSP firmware version:");
	pgf_draw_text(320 + width + 5, 330+slide_y, VITAIDENT_MISC_ITEM_COLOR, patch);
}

static SceVoid Menu_Config(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "Config Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_CONFIG_COLOR, "Config Menu");
	
	pgf_draw_text(320, 180+slide_y, VITAIDENT_CONFIG_NAME_COLOR, "Airplane mode:");
	nameWidth("Airplane mode:");
	pgf_draw_text(320 + width + 5, 180+slide_y, VITAIDENT_CONFIG_ITEM_COLOR, RegMgr_GetInt("/CONFIG/SYSTEM/", "flight_mode")? "enabled" : "disabled");
	
	pgf_draw_text(320, 220+slide_y, VITAIDENT_CONFIG_NAME_COLOR, "Bluetooth:");
	nameWidth("Bluetooth:");
	pgf_draw_text(320 + width + 5, 220+slide_y, VITAIDENT_CONFIG_ITEM_COLOR, RegMgr_GetInt("/CONFIG/BT/", "bt_enable")? "enabled" : "disabled");
	
	pgf_draw_text(320, 260+slide_y, VITAIDENT_CONFIG_NAME_COLOR, "WiFi power save:");
	nameWidth("WiFi power save:");
	pgf_draw_text(320 + width + 5, 260+slide_y, VITAIDENT_CONFIG_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NET/", "wifi_power_save")? "enabled" : "disabled");
	
	pgf_draw_text(320, 300+slide_y, VITAIDENT_CONFIG_NAME_COLOR, "Screen lock passcode:");
	nameWidth("Screen lock passcode:");
	pgf_draw_text(320 + width + 5, 300+slide_y, VITAIDENT_CONFIG_ITEM_COLOR, RegMgr_GetStr("/CONFIG/SECURITY/SCREEN_LOCK/", "passcode"));
	
	snprintf(patch, MAX_PATH_LENGTH, "%ld%%", RegMgr_GetBrightness());
	pgf_draw_text(320, 340+slide_y, VITAIDENT_MISC_NAME_COLOR, "Brightness:");
	nameWidth("Brightness:");
	pgf_draw_text(320 + width + 5, 340+slide_y, VITAIDENT_MISC_ITEM_COLOR, patch);
	
	int volume = 0;
	if (R_SUCCEEDED(sceAVConfigGetSystemVol(&volume)))
	snprintf(patch, MAX_PATH_LENGTH, "%d", volume);
	pgf_draw_text(320, 380+slide_y, VITAIDENT_MISC_NAME_COLOR, "Volume:");
	nameWidth("Volume:");
	pgf_draw_text(320 + width + 5, 380+slide_y, VITAIDENT_MISC_ITEM_COLOR, patch);
}

static SceVoid Menu_PSN(SceVoid)
{
	float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
	
	float _x = vita2d_pgf_text_width(font, FONT_SIZE, "PSN Menu");
	pgf_draw_text(ALIGN_CENTER(179, _x)+51, 58+slide_y, VITAIDENT_TITLE_PSN_COLOR, "PSN Menu");
	
	pgf_draw_text(320, 240+slide_y, VITAIDENT_PSN_NAME_COLOR, "NP:");
	nameWidth("NP:");
	pgf_draw_text(320 + width + 5, 240+slide_y, VITAIDENT_PSN_ITEM_COLOR, RegMgr_GetInt("/CONFIG/NP/", "enable_np")? "enabled" : "disabled");
	
	pgf_draw_text(320, 280+slide_y, VITAIDENT_PSN_NAME_COLOR, "Login ID:");
	nameWidth("Login ID:");
	pgf_draw_text(320 + width + 5, 280+slide_y, VITAIDENT_PSN_ITEM_COLOR, RegMgr_GetStr("/CONFIG/NP/", "login_id"));
	
	pgf_draw_text(320, 320+slide_y, VITAIDENT_PSN_NAME_COLOR, "Password:");
	nameWidth("Password:");
	pgf_draw_text(320 + width + 5, 320+slide_y, VITAIDENT_PSN_ITEM_COLOR, RegMgr_GetStr("/CONFIG/NP/", "password"));
}

void mainMenu(void)
{
		uint32_t vitaident_eC = epileptik2();
		float slide_y = SCREEN_HEIGHT - Vitaident_menu.cur_pos;
		
		vita2d_draw_texture_tint(ico_kernel_menu, 60, 137+slide_y, selection == 0? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_system_menu, 174, 167+slide_y, selection == 1? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_battery_menu, 60, 227+slide_y, selection == 2? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_storage_menu, 174, 257+slide_y, selection == 3? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_wifi_menu, 60, 317+slide_y, selection == 4? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_misc_menu, 174, 347+slide_y, selection == 5? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_config_menu, 60, 407+slide_y, selection == 6? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);
		vita2d_draw_texture_tint(ico_psn_menu, 174, 437+slide_y, selection == 7? RGBA8(VITAIDENT_MENU_R, VITAIDENT_MENU_G, VITAIDENT_MENU_B, vitaident_eC) : WHITE);

        switch (selection)
		{
			case 0:
				Menu_Kernel();
				break;
            case 1:
                Menu_System();
                break;
            case 2:
                Menu_Battery();
                break;
            case 3:
                Menu_Storage();
                break;
            case 4:
                Menu_WiFi();
				
				if (pressed_pad[PAD_LTRIGGER])
				{
					if (wifiPage == 1)
						wifiPage = 0;
				}
				else if (pressed_pad[PAD_RTRIGGER])
				{
					if ((wifiPage == 0) && (strcmp(RegMgr_GetStr("/CONFIG/NET/06/WIFI/", "ssid"), "") != 0))
						wifiPage = 1;
				}
                break;
            case 5:
				Menu_Misc();
				break;
			case 6:
				Menu_Config();
				break;
			case 7:
				Menu_PSN();
				break;
        }
}

static void menuVitaident_HandleTouch()
{	
	if (TouchFront_CheckIsPressed()) 
	{
		if (TouchFront_GetX() >= 60 && TouchFront_GetX() <= 120 && TouchFront_GetY() >= 137 && TouchFront_GetY() <= 197)
			selection = 0;
		else if (TouchFront_GetX() >= 174 && TouchFront_GetX() <= 234 && TouchFront_GetY() >= 167 && TouchFront_GetY() <= 227)
			selection = 1;
		else if (TouchFront_GetX() >= 60 && TouchFront_GetX() <= 120 && TouchFront_GetY() >= 227 && TouchFront_GetY() <= 287)
			selection = 2;
		else if (TouchFront_GetX() >= 174 && TouchFront_GetX() <= 234 && TouchFront_GetY() >= 257 && TouchFront_GetY() <= 317)
			selection = 3;
		else if (TouchFront_GetX() >= 60 && TouchFront_GetX() <= 120 && TouchFront_GetY() >= 317 && TouchFront_GetY() <= 377)
			selection = 4;
		else if (TouchFront_GetX() >= 174 && TouchFront_GetX() <= 234 && TouchFront_GetY() >= 347 && TouchFront_GetY() <= 407)
			selection = 5;
		else if (TouchFront_GetX() >= 60 && TouchFront_GetX() <= 120 && TouchFront_GetY() >= 407 && TouchFront_GetY() <= 467)
			selection = 6;
		else if (TouchFront_GetX() >= 174 && TouchFront_GetX() <= 234 && TouchFront_GetY() >= 437 && TouchFront_GetY() <= 497)
			selection = 7;
	}
}

void drawVitaidentMenu() {
  
	if (Vitaident_menu.status == VITAIDENT_MENU_CLOSED)
		return;

	// Closing settings menu
	if (Vitaident_menu.status == VITAIDENT_MENU_CLOSING) {
		if (Vitaident_menu.cur_pos > 0.0f) {
			Vitaident_menu.cur_pos -= easeOut(0.0f, Vitaident_menu.cur_pos, 0.25f, 0.01f);
		} else {
			Vitaident_menu.status = VITAIDENT_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (Vitaident_menu.status == VITAIDENT_MENU_OPENING) {
		if (Vitaident_menu.cur_pos < SCREEN_HEIGHT) {
			Vitaident_menu.cur_pos += easeOut(Vitaident_menu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			Vitaident_menu.status = VITAIDENT_MENU_OPENED;
		}
	}

	// Draw settings menu
	vita2d_draw_texture(vitaident_image, 0.0f, Vitaident_menu.cur_pos - SCREEN_HEIGHT);
	
	mainMenu();
}

static int agreement = VITAIDENT_AGREEMENT_NONE;

void VitaidentAgree() {
	agreement = VITAIDENT_AGREEMENT_AGREE;
}

void VitaidentDisagree() {
	agreement = VITAIDENT_AGREEMENT_DISAGREE;
}

void VitaidentMenuCtrl() {
	TouchFront_Update();
	TouchBack_Update();

	// Agreement
	if (agreement != VITAIDENT_AGREEMENT_NONE) {
		agreement = VITAIDENT_AGREEMENT_NONE;
	}

		if(pressed_pad[PAD_DOWN]){
			selection++; //Moves the selector down
		}
        else if(pressed_pad[PAD_UP]){
			selection--; //Moves the selector up
		}
		else if(pressed_pad[PAD_CANCEL]){
			closeVitaidentMenu();
		}else if (TouchBack_CheckIsPressed()) 
		{
			if (TouchBack_GetX() >= 0 && TouchBack_GetX() <= 960 && TouchBack_GetY() >= 0 && TouchBack_GetY() <= 544)
				closeVitaidentMenu();
		}
        
		menuVitaident_HandleTouch();
		
        if (selection > MAX_ITEMS) 
			selection = 0; //Sets the selection to the first
        if (selection < 0) 
			selection = MAX_ITEMS; //Sets the selection back to last
}
