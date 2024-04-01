/*
	VitaBooks
	Copyright (C) 2015-2017, BenMitnicK

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __LOADIMAGES_H__
#define __LOADIMAGES_H__

#include "file.h"

vita2d_texture *loadImages(const char *file, int type);
int isHorizontale(float rad);
int getNextZoomModes(float *zoom, float width, float height, float rad, int mode);
void resetImagesInfo(vita2d_texture *tex, float *width, float *height, float *x, float *y, float *rad, float *zoom, int *mode, uint64_t *time);

#endif