/*
		
		Taken from VitaComix by Arkanite.
		A manga/comic book reader for the Playstation Vita
		
		File: touch.c
		
*/
#include <malloc.h>

#include "touch.h"

static TouchStateData* touchFrontState;
static TouchStateData* touchBackState;

SceInt TouchFront_Init(SceVoid) 
{
	sceTouchSetSamplingState(SCE_TOUCH_PORT_FRONT, 1);
	
	touchFrontState = malloc(sizeof(TouchStateData));
	touchFrontState->posX = 0;
	touchFrontState->posY = 0;
	touchFrontState->hold = 0;
	touchFrontState->pressed = 0;
	touchFrontState->pressedPrev = 0;
	touchFrontState->released = 0;
	touchFrontState->releasedPrev = 0;
	
	return 1;
}

SceInt TouchBack_Init(SceVoid) 
{
	sceTouchSetSamplingState(SCE_TOUCH_PORT_BACK, 1);
	
	touchBackState = malloc(sizeof(TouchStateData));
	touchBackState->posX = 0;
	touchBackState->posY = 0;
	touchBackState->hold = 0;
	touchBackState->pressed = 0;
	touchBackState->pressedPrev = 0;
	touchBackState->released = 0;
	touchBackState->releasedPrev = 0;
	
	return 1;
}

SceInt TouchFront_GetX(SceVoid) 
{
	return touchFrontState->posX;
}

SceInt TouchFront_GetY(SceVoid) 
{
	return touchFrontState->posY;
}

SceInt TouchFront_CheckIsPressed(SceVoid) 
{
	return touchFrontState->pressed;
}

SceInt TouchFront_CheckIsReleased(SceVoid) 
{
	return touchFrontState->released;
}

SceInt TouchFront_CheckIsHold(SceVoid) 
{
	return touchFrontState->hold;
}
	
SceInt TouchBack_GetX(SceVoid) 
{
	return touchBackState->posX;
}

SceInt TouchBack_GetY(SceVoid) 
{
	return touchBackState->posY;
}

SceInt TouchBack_CheckIsPressed(SceVoid) 
{
	return touchBackState->pressed;
}

SceInt TouchBack_CheckIsReleased(SceVoid) 
{
	return touchBackState->released;
}

SceInt TouchBack_CheckIsHold(SceVoid) 
{
	return touchBackState->hold;
}	

SceVoid TouchFront_Update(SceVoid) 
{
	sceTouchPeek(SCE_TOUCH_PORT_FRONT, &touch, 1);
	
	if (touch.reportNum > 0) 
	{
		touchFrontState->hold = 1;
		touchFrontState->posX = (lerp(touch.report[0].x, 1919, 960));
		touchFrontState->posY = (lerp(touch.report[0].y, 1087, 544));
		touchFrontState->released = 0;
		touchFrontState->releasedPrev = 0;
		if (touchFrontState->pressedPrev == 0) 
		{
			touchFrontState->pressedPrev = 1;
			touchFrontState->pressed = 1;
		}
		else 
		{
			touchFrontState->pressed = 0;
		}
	}
	else 
	{
		touchFrontState->hold = 0;
		touchFrontState->pressed = 0;
		touchFrontState->pressedPrev = 0;
		if (touchFrontState->releasedPrev == 0) 
		{
			touchFrontState->releasedPrev = 1;
			touchFrontState->released = 1;
		}
		else 
		{
			touchFrontState->released = 0;			
		}
	}
}

SceVoid TouchBack_Update(SceVoid) 
{
	sceTouchPeek(SCE_TOUCH_PORT_BACK, &touch, 1);
	
	if (touch.reportNum > 0) 
	{
		touchBackState->hold = 1;
		touchBackState->posX = (lerp(touch.report[0].x, 1919, 960));
		touchBackState->posY = (lerp(touch.report[0].y, 1087, 544));
		touchBackState->released = 0;
		touchBackState->releasedPrev = 0;
		if (touchBackState->pressedPrev == 0) 
		{
			touchBackState->pressedPrev = 1;
			touchBackState->pressed = 1;
		}
		else 
		{
			touchBackState->pressed = 0;
		}
	}
	else 
	{
		touchBackState->hold = 0;
		touchBackState->pressed = 0;
		touchBackState->pressedPrev = 0;
		if (touchBackState->releasedPrev == 0) 
		{
			touchBackState->releasedPrev = 1;
			touchBackState->released = 1;
		}
		else 
		{
			touchBackState->released = 0;
			
		}
	}
}
