/*
	VitaTweakBox
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

#include "main.h"
#include "browser.h"
#include "archive.h"
#include "theme.h"
#include "loadimages.h"
#include "utils.h"
#include "file.h"
#include "photo.h"

vita2d_texture *loadImages(const char *file, int type) {
		vita2d_texture *tex = NULL;
		
		switch (type) {
			case FILE_TYPE_BMP:
				tex = vita2d_load_BMP_file(file);
				break;
			
			case FILE_TYPE_PNG:
				tex = vita2d_load_PNG_file(file);
				break;
				
			case FILE_TYPE_JPEG:
				tex = vita2d_load_JPEG_file(file);
				break;
		}

	// Set bilinear filter
	if (tex)
		vita2d_texture_set_filters(tex, SCE_GXM_TEXTURE_FILTER_LINEAR, SCE_GXM_TEXTURE_FILTER_LINEAR);
	
	return tex;
}

int isHorizontale(float rad) {
	return ((int)sinf(rad) == 0) ? 1 : 0;
}

static void photoMode(float *zoom, float width, float height, float rad, int mode) {
  int horizontal = isHorizontale(rad);
  float h = horizontal ? height : width;
  float w = horizontal ? width : height;

  switch (mode) {
    case MODE_CUSTOM:
      break;
      
    case MODE_PERFECT: // this is only used for showing image the first time
      if (h > SCREEN_HEIGHT) { // first priority, fit height
        *zoom = SCREEN_HEIGHT / h;
      } else if (w > SCREEN_WIDTH) { // second priority, fit screen
        *zoom = SCREEN_WIDTH / w;
      } else { // otherwise, original size
        *zoom = 1.0f;
      }

      break;
    
    case MODE_ORIGINAL:
      *zoom = 1.0f;
      break;
      
    case MODE_FIT_HEIGHT:
      *zoom = SCREEN_HEIGHT / h;
      break;
      
    case MODE_FIT_WIDTH:
      *zoom = SCREEN_WIDTH / w;
      break;
  }
}

int getNextZoomModes(float *zoom, float width, float height, float rad, int mode) {
  float next_zoom = ZOOM_MAX, smallest_zoom = ZOOM_MAX;;
  int next_mode = MODE_ORIGINAL, smallest_mode = MODE_ORIGINAL;

  int i = 0;
  while (i < 3) {
    if (mode == MODE_CUSTOM || mode == MODE_PERFECT || mode == MODE_FIT_WIDTH) {
      mode = MODE_ORIGINAL;
    } else {
      mode++;
    }

    float new_zoom = 0.0f;
    photoMode(&new_zoom, width, height, rad, mode);

    if (new_zoom < smallest_zoom) {
      smallest_zoom = new_zoom;
      smallest_mode = mode;
    }

    if (new_zoom > *zoom && new_zoom < next_zoom) {
      next_zoom = new_zoom;
      next_mode = mode;
    }

    i++;
  }

  // Get smallest then
  if (next_zoom == ZOOM_MAX) {
    next_zoom = smallest_zoom;
    next_mode = smallest_mode;
  }

  *zoom = next_zoom;
  return next_mode;
}

void resetImagesInfo(vita2d_texture *tex, float *width, float *height, float *x, float *y, float *rad, float *zoom, int *mode, uint64_t *time) {
  *width = vita2d_texture_get_width(tex);
  *height = vita2d_texture_get_height(tex);

  *x = *width/2.0f;
  *y = *height/2.0f;

  *rad = 0;
  *zoom = 1.0f;

  *mode = MODE_PERFECT;
  photoMode(zoom, *width, *height, *rad, *mode);

  *time = 0;
}
