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

#include "../main.h"
#include "../browser.h"
#include "../archive.h"
#include "../language.h"
#include "../theme.h"
#include "../init.h"
#include "../utils.h"
#include "../loadimages.h"
#include "../file.h"
#include "../photo.h"
#include "../ime_dialog.h"
#include "../touch.h"
#include "../help.h" //BMK
#include "book.h"
#include "book_images.h"
#include "images_menu.h"

int bookcount;
int BookOffset;

static char **bookImagesPatch_options = NULL;
char **bookImagesType_options = NULL;
static int bookImages_count;

void initBookImagesArray(){
	
	bookImagesType_options = malloc(MAX_IMAGES * sizeof(char *));
	bookImagesPatch_options = malloc(MAX_IMAGES * sizeof(char *));
	
	for (int i = 0; i < MAX_IMAGES; i++){
		bookImagesType_options[i] = malloc(MAX_IMAGE_LENGTH);
		bookImagesPatch_options[i] = malloc(MAX_IMAGE_LENGTH);
	}
}

static int check_for_book_images_content(char *path) {
	SceUID dfd = sceIoDopen(path);

	if (dfd >= 0) {
		int res = 0;
		int i = 0;	
		int type;
		bookcount = 0;
		bookImages_count = 0;
		
		do {
			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));
			res = sceIoDread(dfd, &dir);
			if (res > 0) {				
					if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0 || strcmp(dir.d_name, "cover.png") == 0 || strcmp(dir.d_name, "Cover.png") == 0 || strcmp(dir.d_name, "cover.jpg") == 0 || strcmp(dir.d_name, "Cover.jpg") == 0)
						continue;
					
					strncpy(bookImagesType_options[bookImages_count], dir.d_name, MAX_IMAGE_LENGTH);
					char patch[MAX_IMAGE_LENGTH];
					snprintf(patch, MAX_IMAGE_LENGTH, "%s%s", path, dir.d_name);
					strncpy(bookImagesPatch_options[bookImages_count], patch, MAX_IMAGE_LENGTH);
					
					i++;	
					bookImages_count++;
				}
		} while (res > 0 && bookImages_count < MAX_IMAGES);
		bookcount = i;
		sceIoDclose(dfd);
		return bookcount;
	}

	return 0;
}

int loadPreviewBookImages(char *name){
	
	char path[MAX_PATH_LENGTH];
	snprintf(path, MAX_PATH_LENGTH, "ux0:books/%s/", name);
	
	int bookImagesfound = 0;	
	bookImagesfound = check_for_book_images_content(path);

	if(bookImagesfound == 0){
		
		while (1) {
			
		  readPad();
		
		  if (pressed_pad[PAD_TRIANGLE]){
			  
			  break;
			  
		  }
		
		// Start drawing
		startDrawing2();

		float x = vita2d_pgf_text_width(font, FONT_SIZE, language_container[BOOKS_NO_IMAGES]);
		float y = vita2d_pgf_text_height(font, FONT_SIZE, language_container[BOOKS_NO_IMAGES]);
		pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), ALIGN_CENTER(SCREEN_HEIGHT, y), BOOK_NO_IMAGES_COLOR, language_container[BOOKS_NO_IMAGES]);

		// End drawing
		endDrawing();
		}
		vita2d_wait_rendering_done();
	}else{
		
	// Init book menu
	initBookImagesMenu();
	// Init help menu BMK
	initHelpMenu();
	
	BookOffset = 0;
	int type;
	type = getFileType(bookImagesType_options[BookOffset]);
	vita2d_texture *tex = loadImages(bookImagesPatch_options[BookOffset], type);
	if (!tex) {
		return VITASHELL_ERROR_NO_MEMORY;
	}
	// Variables
	float width = 0.0f, height = 0.0f, x = 0.0f, y = 0.0f, rad = 0.0f, zoom = 1.0f;
	int mode = MODE_PERFECT;
	uint64_t time = 0;
	resetImagesInfo(tex, &width, &height, &x, &y, &rad, &zoom, &mode, &time);
	
	while (1) {
		
		  readPad();
		  TouchFront_Update();
		
		  if (pressed_pad[PAD_TRIANGLE]){
			break;
		  }
		  
		  // help
		if (pressed_pad[PAD_START]) {
			if (getHelpMenuStatus() != HELP_MENU_CLOSED) {
			  closeHelpMenu(); //BMK
			} else{
				if (getBookImagesMenuStatus() != BOOK_IMAGES_MENU_CLOSED){
					closeBookImagesMenu();
				}
			  openHelpMenu(6); //BMK
			}
		}
		  
		  if (pressed_pad[PAD_LEFT] || current_pad[PAD_LTRIGGER] || hold_pad[PAD_LEFT]){
			if(BookOffset > 0)
			{
					
				BookOffset--;
				
				type = getFileType(bookImagesType_options[BookOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[BookOffset], type);
					if (!tex) {
					  return VITASHELL_ERROR_NO_MEMORY;
					}

					// Reset image
					resetImagesInfo(tex, &width, &height, &x, &y, &rad, &zoom, &mode, &time);
				}
			}
		  
		  }else if(pressed_pad[PAD_RIGHT] || current_pad[PAD_RTRIGGER] || hold_pad[PAD_RIGHT]){
			if(BookOffset < bookcount-1)
			{
					
				BookOffset++;
					
				type = getFileType(bookImagesType_options[BookOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[BookOffset], type);
					if (!tex) {
					  return VITASHELL_ERROR_NO_MEMORY;
					}

					// Reset image
					resetImagesInfo(tex, &width, &height, &x, &y, &rad, &zoom, &mode, &time);
				}
			}		  
		  }
		  
		if (TouchFront_CheckIsPressed()) 
		{
			if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 90 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
				if(BookOffset > 0)
				{
						
					BookOffset--;
					
					type = getFileType(bookImagesType_options[BookOffset]);
					if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
						vita2d_wait_rendering_done();
						vita2d_free_texture(tex);
						
						tex = loadImages(bookImagesPatch_options[BookOffset], type);
						if (!tex) {
						  return VITASHELL_ERROR_NO_MEMORY;
						}

						// Reset image
						resetImagesInfo(tex, &width, &height, &x, &y, &rad, &zoom, &mode, &time);
					}
				}
			}
			else if (TouchFront_GetX() >= 870 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
				if(BookOffset < bookcount-1)
				{
						
					BookOffset++;
						
					type = getFileType(bookImagesType_options[BookOffset]);
					if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
						vita2d_wait_rendering_done();
						vita2d_free_texture(tex);
						
						tex = loadImages(bookImagesPatch_options[BookOffset], type);
						if (!tex) {
						  return VITASHELL_ERROR_NO_MEMORY;
						}

						// Reset image
						resetImagesInfo(tex, &width, &height, &x, &y, &rad, &zoom, &mode, &time);
					}
				}		
			}
			else if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 0 && TouchFront_GetY() <= 454){
				if (getBookImagesMenuStatus() != BOOK_IMAGES_MENU_CLOSED){
					closeBookImagesMenu();
				}else{
					if (getHelpMenuStatus() != HELP_MENU_CLOSED) {
					  closeHelpMenu(); //BMK
					}
					openBookImagesMenu();
				}
			}
		}
		  
		  // Photo mode
		  if (pressed_pad[PAD_ENTER]) {
		  time = sceKernelGetProcessTimeWide();

		  x = width / 2.0f;
		  y = height / 2.0f;

		  // Find next mode
		  mode = getNextZoomModes(&zoom, width, height, rad, mode);
		}
		
		
		
		// Zoom
		if (current_pad[PAD_RIGHT_ANALOG_DOWN]) {
		  time = sceKernelGetProcessTimeWide();
		  mode = MODE_CUSTOM;
		  zoom /= ZOOM_FACTOR;
		} else if (current_pad[PAD_RIGHT_ANALOG_UP]) {
		  time = sceKernelGetProcessTimeWide();
		  mode = MODE_CUSTOM;
		  zoom *= ZOOM_FACTOR;
		}
		
		if (zoom < ZOOM_MIN) {
		  zoom = ZOOM_MIN;
		}

		if (zoom > ZOOM_MAX) {
		  zoom = ZOOM_MAX;
		}

		// Move
		if (pad.lx < (ANALOG_CENTER - ANALOG_SENSITIVITY) || pad.lx > (ANALOG_CENTER + ANALOG_SENSITIVITY)) {
		  float d = ((pad.lx - ANALOG_CENTER) / MOVE_DIVISION) / zoom;

		  if (isHorizontale(rad)) {
			x += cosf(rad) * d;
		  } else {
			y += -sinf(rad) * d;
		  }
		}

		if (pad.ly < (ANALOG_CENTER - ANALOG_SENSITIVITY) || pad.ly > (ANALOG_CENTER + ANALOG_SENSITIVITY)) {
		  float d = ((pad.ly - ANALOG_CENTER) / MOVE_DIVISION) / zoom;

		  if (isHorizontale(rad)) {
			y += cosf(rad) * d;
		  } else {
			x += sinf(rad) * d;
		  }
		}

		// Limit
		int horizontal = isHorizontale(rad);
		float w = horizontal ? SCREEN_HALF_WIDTH : SCREEN_HALF_HEIGHT;
		float h = horizontal ? SCREEN_HALF_HEIGHT : SCREEN_HALF_WIDTH;

		if ((zoom *  width) > 2.0f * w) {
		  if (x < (w / zoom)) {
			x = w / zoom;
		  } else if (x > (width - w / zoom)) {
			x = width - w / zoom;
		  }
		} else {
		  x = width / 2.0f;
		}

		if ((zoom * height) > 2.0f * h) {
		  if (y < (h / zoom)) {
			y = h / zoom;
		  } else if (y > (height - h / zoom)) {
			y = height - h/zoom;
		  }
		} else {
		  y = height / 2.0f;
		}
		
		// Start drawing
		startDrawing2();
		
		// Photo
		vita2d_draw_texture_scale_rotate_hotspot(tex, SCREEN_HALF_WIDTH, SCREEN_HALF_HEIGHT, zoom, zoom, rad, x, y);		
		
		// Zoom text
		if ((sceKernelGetProcessTimeWide() - time) < ZOOM_TEXT_TIME)
		pgf_draw_textf(SHELL_MARGIN_X, SCREEN_HEIGHT - 3.0f * SHELL_MARGIN_Y, PHOTO_ZOOM_COLOR, "%.0f%%", zoom * 100.0f);
		
		// Draw book menu
		drawBookImagesMenu();
		// help drawing
		drawHelpMenu();

		// End drawing
		endDrawing();
		}
		vita2d_wait_rendering_done();
		vita2d_free_texture(tex);
	
		if (getHelpMenuStatus() != HELP_MENU_CLOSED) {
			closeHelpMenu(); //BMK
		}
	}
	
	return 0;
}
