/*
		
		Taken from VitaComix by Arkanite.
		A manga/comic book reader for the Playstation Vita
		
		File: touch.c
		
*/
#ifndef TOUCH_H
#define TOUCH_H

#include <vitasdk.h>

#define lerp(value, from_max, to_max) ((((value * 10) * (to_max * 10)) / (from_max * 10)) / 10)

#define touchInRect(x1, x2, y1, y2)  ((TouchFront_CheckIsPressed()) && (TouchFront_GetX() >= (x1) && TouchFront_GetX() <= (x2) && TouchFront_GetY() >= (y1) && TouchFront_GetY() <= (y2)))
#define touchInRect2(x1, x2, y1, y2)  ((TouchBack_CheckIsPressed()) && (TouchBack_GetX() >= (x1) && TouchBack_GetX() <= (x2) && TouchBack_GetY() >= (y1) && TouchBack_GetY() <= (y2)))

extern SceTouchData touch;
//SceTouchData touchBack;

typedef struct 
{
	int posX;
	int posY;
	int hold;
	int pressed;
	int pressedPrev;
	int released;
	int releasedPrev;
} TouchStateData;

SceInt TouchFront_Init();
SceVoid TouchFront_Update(SceVoid);

SceInt TouchFront_GetX(SceVoid);
SceInt TouchFront_GetY(SceVoid);
SceInt TouchFront_CheckIsPressed(SceVoid);
SceInt TouchFront_CheckIsReleased(SceVoid);
SceInt TouchFront_CheckIsHold(SceVoid);

SceInt TouchBack_Init();
SceVoid TouchBack_Update(SceVoid);

SceInt TouchBack_GetX(SceVoid);
SceInt TouchBack_GetY(SceVoid);
SceInt TouchBack_CheckIsPressed(SceVoid);
SceInt TouchBack_CheckIsReleased(SceVoid);
SceInt TouchBack_CheckIsHold(SceVoid);

#endif
