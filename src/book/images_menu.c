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

#include "../main.h"
#include "../init.h"
#include "../utils.h"
#include "images_menu.h"

static int n_Book_Images_entries = 0;
static BookImagesMenu book_images_menu;
char az[MAX_PATH_LENGTH];
char za[MAX_PATH_LENGTH];

vita2d_texture *book_image = NULL;

void initBookImagesMenu() {
	memset(&book_images_menu, 0, sizeof(BookImagesMenu));
	book_images_menu.status = BOOK_IMAGES_MENU_CLOSED;
	n_Book_Images_entries = 1;	
}

void openBookImagesMenu() {
	book_images_menu.status = BOOK_IMAGES_MENU_OPENING;
	snprintf(az, MAX_PATH_LENGTH, "%d", bookcount);
}

void closeBookImagesMenu() {
	book_images_menu.status = BOOK_IMAGES_MENU_CLOSING;
}

int getBookImagesMenuStatus() {
	return book_images_menu.status;
}

void drawBookImagesMenu() {
	if (book_images_menu.status == BOOK_IMAGES_MENU_CLOSED)
		return;

	// Closing settings menu
	if (book_images_menu.status == BOOK_IMAGES_MENU_CLOSING) {
		if (book_images_menu.cur_pos > 0.0f) {
			book_images_menu.cur_pos -= easeOut(0.0f, book_images_menu.cur_pos, 0.25f, 0.01f);
		} else {
			book_images_menu.status = BOOK_IMAGES_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (book_images_menu.status == BOOK_IMAGES_MENU_OPENING) {
		if (book_images_menu.cur_pos < SCREEN_HEIGHT) {
			book_images_menu.cur_pos += easeOut(book_images_menu.cur_pos, 60, 0.25f, 0.01f);
		} else {
			book_images_menu.status = BOOK_IMAGES_MENU_OPENED;
		}
	}
	
	if (!book_image) {
	book_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(book_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = 0xE0231f1b;
			}
		}
	}
	
	snprintf(za, MAX_PATH_LENGTH, "%d", BookOffset+1);
	float _x = 0;
	if(BookOffset >= 9){
		_x = 10;
	}
	// Draw menu
	vita2d_draw_texture(book_image, 0.0f, SCREEN_HEIGHT - book_images_menu.cur_pos);
	float y = SCREEN_HEIGHT - book_images_menu.cur_pos;
	float x = vita2d_pgf_text_width(font, FONT_SIZE, bookImagesType_options[BookOffset]);
	pgf_draw_text(ALIGN_CENTER(SCREEN_WIDTH, x), y+20, WHITE, bookImagesType_options[BookOffset]);
	pgf_draw_text(880, y+20, WHITE, za);
	pgf_draw_text(900+_x, y+20, WHITE, "/");
	pgf_draw_text(910+_x, y+20, WHITE, az);
	
}