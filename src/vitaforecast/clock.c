#include "clock.h"
#include "forecast.h"
#include "../main.h"

static char patch[MAX_PATH_LENGTH];

void getDayOfWeek(int x, int y, int style, float size)
{
	SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);

	int day = sceRtcGetDayOfWeek(time.year, time.month, time.day);

    static const char days[7][16] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    
    char buffer[16];
	sprintf(buffer, "%s", days[day]);
    
    if(style == 1)
        buffer[3] = 0;
        
    pgf2_draw_text(x, y, RGBA8(255, 255, 255, 255), size, buffer);
}
	
void getMonthOfYear(int x, int y, float size)
{
	static const char months[12][16] =
	{
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"
	};
       
    SceDateTime time;
	sceRtcGetCurrentClockLocalTime(&time);
	snprintf(patch, MAX_PATH_LENGTH, "%d %s", time.day, months[time.month - 1]);
    pgf2_draw_text(x, y, RGBA8(255, 255, 255, 255), size, patch);
}