/*
	VitaShell
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
#include "../language.h"
#include "../utils.h"
#include "../theme.h"
#include "../touch.h"
#include "../io_process.h"
#include "../archive.h"
#include "../file.h"
#include "../photo.h"
#include "../loadimages.h"
#include "../settings.h"
#include "book.h"
#include "book_images.h"

static int n_Book_entries = 0;
static BookMenu bookmenu;
static char debug[MAX_PATH_LENGTH];
static char **bookImagesPatch_options = NULL;
static char **bookImagesType_options = NULL;
static vita2d_texture *tex = NULL;
static int type;
static char patch[MAX_PATH_LENGTH];

static int book_count;
static int bookCover_count;
static int count = 0;
static int NavOffset = 0;
static char **book_options = NULL;
static int bookPage = 0;
static int bookfound = 0;

static int check_for_book_cover_content(char *path) {
	SceUID dfd = sceIoDopen(path);

	if (dfd >= 0) {
		int res = 0;
		int i = 0;	
		int covercount = 0;
		
		do {
			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));
			res = sceIoDread(dfd, &dir);
			if (res > 0) {				
					if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0)
						continue;
					
					if(strcmp(dir.d_name, "cover.png") == 0){
						strncpy(bookImagesType_options[bookCover_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(bookImagesPatch_options[bookCover_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "Cover.png") == 0){
						strncpy(bookImagesType_options[bookCover_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(bookImagesPatch_options[bookCover_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "cover.jpg") == 0){
						strncpy(bookImagesType_options[bookCover_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(bookImagesPatch_options[bookCover_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}else if(strcmp(dir.d_name, "Cover.jpg") == 0){
						strncpy(bookImagesType_options[bookCover_count], dir.d_name, MAX_PATH_LENGTH);
						snprintf(patch, MAX_PATH_LENGTH, "%s%s", path, dir.d_name);
						strncpy(bookImagesPatch_options[bookCover_count], patch, MAX_PATH_LENGTH);
						covercount = 1;
						break;
					}
					
					i++;	
				}
		} while (res > 0);
		
		if (!covercount){
			snprintf(patch, MAX_PATH_LENGTH, "ux0:VitaTweakBox/theme/%s/vtb/no_cover.png", themeActual);
			if (checkFileExist(patch)){
				strncpy(bookImagesType_options[bookCover_count], "no_cover.png", MAX_PATH_LENGTH);
				strncpy(bookImagesPatch_options[bookCover_count], patch, MAX_PATH_LENGTH);
			}else{
				strncpy(bookImagesType_options[bookCover_count], "no_cover.png", MAX_PATH_LENGTH);
				strncpy(bookImagesPatch_options[bookCover_count], "ux0:VitaTweakBox/theme/Default/vtb/no_cover.png", MAX_PATH_LENGTH);
			}
		}
		covercount = 0;
		sceIoDclose(dfd);
	}

	return 0;
}

int check_for_book_content(char *path) {
	SceUID dfd = sceIoDopen(path);
	
	if (dfd >= 0) {
		int res = 0;
		int i = 0;
		book_count = 0;		

		do {
			SceIoDirent dir;
			memset(&dir, 0, sizeof(SceIoDirent));
			res = sceIoDread(dfd, &dir);
			if (res > 0) {
				if (SCE_S_ISDIR(dir.d_stat.st_mode)) {
					if (strcmp(dir.d_name, ".") == 0 || strcmp(dir.d_name, "..") == 0)
						continue;
					
					strncpy(book_options[book_count], dir.d_name, MAX_BOOK_LENGTH);
					snprintf(patch, MAX_PATH_LENGTH, "%s%s/", path, dir.d_name);
					
					i++;	
					book_count++;						
					}
				}
		} while (res > 0 && book_count < MAX_BOOKS);
		count = i;	
		sceIoDclose(dfd);
		return count;
	}
	
	return 0;
}

void initBookMenu() {
	memset(&bookmenu, 0, sizeof(BookMenu));
	bookmenu.status = BOOK_MENU_CLOSED;
	n_Book_entries = 1;	
	
	book_options = malloc(MAX_BOOKS * sizeof(char *));
	bookImagesType_options = malloc(MAX_BOOKS * sizeof(char *));
	bookImagesPatch_options = malloc(MAX_BOOKS * sizeof(char *));
	
	for (int i = 0; i < MAX_BOOKS; i++){
		book_options[i] = malloc(MAX_BOOK_LENGTH);
		bookImagesType_options[i] = malloc(MAX_PATH_LENGTH);
		bookImagesPatch_options[i] = malloc(MAX_PATH_LENGTH);
	}
	
	bookfound = check_for_book_content("ux0:books/");
	
	for (bookCover_count = 0; bookCover_count < count; bookCover_count++){
		snprintf(patch, MAX_PATH_LENGTH, "ux0:books/%s/", book_options[bookCover_count]);
		check_for_book_cover_content(patch);
	}
	
	type = getFileType(bookImagesType_options[NavOffset]);
	tex = loadImages(bookImagesPatch_options[NavOffset], type);
}

void openBookMenu() {
	bookmenu.status = BOOK_MENU_OPENING;
}

void closeBookMenu() {
	bookmenu.status = BOOK_MENU_CLOSING;
	NavOffset = 0;
	type = getFileType(bookImagesType_options[NavOffset]);
	if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
		vita2d_wait_rendering_done();
		vita2d_free_texture(tex);
				
		tex = loadImages(bookImagesPatch_options[NavOffset], type);
	}
}

int getBookMenuStatus() {
	return bookmenu.status;
}

void loadBooks(){
	
	float slide_y = bookmenu.cur_pos - SCREEN_HEIGHT;
	
	if(bookfound == 0){

		float x = vita2d_pgf_text_width(font, 1.2, language_container[NO_BOOKS_FOUND]);
		float tx = vita2d_texture_get_width(no_cover_image);
		float ty = vita2d_texture_get_height(no_cover_image);
		
		vita2d_draw_rectangle(ALIGN_CENTER(SCREEN_WIDTH, tx), 63+slide_y, tx, ty, RGBA8(0, 0, 0, 100));
		pgf2_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), 232+slide_y, WHITE, 1.2, language_container[NO_BOOKS_FOUND]);
		
	}else{
	
		float x = vita2d_pgf_text_width(font, 1.2, book_options[NavOffset]);
		float tx = vita2d_texture_get_width(tex);

		vita2d_draw_texture(tex, ALIGN_CENTER(SCREEN_WIDTH, tx), 63+slide_y);
		
		pgf2_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), 475+slide_y, WHITE, 1.2,book_options[NavOffset]);
	}
	
}

void drawBookMenu() {
	if (bookmenu.status == BOOK_MENU_CLOSED)
		return;

	// Closing settings menu
	if (bookmenu.status == BOOK_MENU_CLOSING) {
		if (bookmenu.cur_pos > 0.0f) {
			bookmenu.cur_pos -= easeOut(0.0f, bookmenu.cur_pos, 0.25f, 0.01f);
		} else {
			bookmenu.status = BOOK_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (bookmenu.status == BOOK_MENU_OPENING) {
		if (bookmenu.cur_pos < SCREEN_HEIGHT) {
			bookmenu.cur_pos += easeOut(bookmenu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			bookmenu.status = BOOK_MENU_OPENED;
		}
	}
	
	// Draw book menu
	vita2d_draw_texture(bg_book_image, 0.0f, bookmenu.cur_pos - SCREEN_HEIGHT);
	
	loadBooks();

}

static int agreement = BOOK_AGREEMENT_NONE;

void bookAgree() {
  agreement = BOOK_AGREEMENT_AGREE;
}

void bookDisagree() {
  agreement = BOOK_AGREEMENT_DISAGREE;
}

void BookMenuCtrl() {
	TouchFront_Update();
	TouchBack_Update();
	
	if(pressed_pad[PAD_LEFT] || pressed_pad[PAD_LEFT_ANALOG_LEFT] || hold_pad[PAD_LEFT] || hold_pad[PAD_LEFT_ANALOG_LEFT]){
		if(NavOffset > 0){
			NavOffset--;	
			
			type = getFileType(bookImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[NavOffset], type);
				}
		}
	}else if(pressed_pad[PAD_RIGHT] || pressed_pad[PAD_LEFT_ANALOG_RIGHT] || hold_pad[PAD_RIGHT] || hold_pad[PAD_LEFT_ANALOG_RIGHT]){
		if(NavOffset < count-1){
			NavOffset++;

			type = getFileType(bookImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[NavOffset], type);
				}
		}
	}else if (pressed_pad[PAD_CROSS]){		    
		loadPreviewBookImages(book_options[NavOffset]);
	}
	
	if (TouchFront_CheckIsPressed()) 
	{
		if (TouchFront_GetX() >= 0 && TouchFront_GetX() <= 90 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
			if(NavOffset > 0){
			NavOffset--;	
			
			type = getFileType(bookImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[NavOffset], type);
				}
			}
		}
		else if (TouchFront_GetX() >= 870 && TouchFront_GetX() <= 960 && TouchFront_GetY() >= 454 && TouchFront_GetY() <= 544){
			if(NavOffset < count-1){
			NavOffset++;

			type = getFileType(bookImagesType_options[NavOffset]);
				if (type == FILE_TYPE_BMP || type == FILE_TYPE_JPEG || type == FILE_TYPE_PNG) {
					vita2d_wait_rendering_done();
					vita2d_free_texture(tex);
					
					tex = loadImages(bookImagesPatch_options[NavOffset], type);
				}
			}
		}
	}
	
	if (TouchFront_CheckIsReleased())
	{
		if (TouchFront_GetX() >= 459 && TouchFront_GetX() <= 599 && TouchFront_GetY() >= 451 && TouchFront_GetY() <= 510){
			loadPreviewBookImages(book_options[NavOffset]);
		}
	}
	
	// Close
	if (pressed_pad[PAD_CANCEL]) {
		closeBookMenu();
	}else if (TouchBack_CheckIsPressed()) 
	{
		if (TouchBack_GetX() >= 0 && TouchBack_GetX() <= 960 && TouchBack_GetY() >= 0 && TouchBack_GetY() <= 220)
			closeBookMenu();
	}
}