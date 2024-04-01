#ifndef _PROGRESS_BAR_H_
#define _PROGRESS_BAR_H_

#include "../main.h"

SceVoid ProgressBar_DisplayProgress(char *msg, char *src, SceULong64 offset, SceULong64 size);

#endif