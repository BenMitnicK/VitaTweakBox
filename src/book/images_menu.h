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

#ifndef __IMAGES_MENU_H__
#define __IMAGES_MENU_H__

enum BookImagesMenuStatus {
	BOOK_IMAGES_MENU_CLOSED,
	BOOK_IMAGES_MENU_CLOSING,
	BOOK_IMAGES_MENU_OPENED,
	BOOK_IMAGES_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
	int entry_sel;
	int option_sel;
	int n_options;
} BookImagesMenu;

extern char **bookImagesType_options;
extern int bookcount;
extern int BookOffset;

void initBookImagesMenu();
void openBookImagesMenu();
void closeBookImagesMenu();
int getBookImagesMenuStatus();
void drawBookImagesMenu();

#endif