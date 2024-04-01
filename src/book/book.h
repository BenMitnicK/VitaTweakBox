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

#ifndef __BOOK_H__
#define __BOOK_H__

#define MAX_BOOKS 20
#define MAX_BOOK_LENGTH 20

#define MAX_IMAGES 100
#define MAX_IMAGE_LENGTH 100

// Main
#define COVER_MARGIN_X 20.0f
#define COVER_MARGIN_X2 82.0f
#define COVER_MARGIN_Y 22.0f
#define COVER_MARGIN_Y2 20.0f

enum BookAgreement {
  BOOK_AGREEMENT_NONE,
  BOOK_AGREEMENT_AGREE,
  BOOK_AGREEMENT_DISAGREE,
};

enum BookMenuStatus {
	BOOK_MENU_CLOSED,
	BOOK_MENU_CLOSING,
	BOOK_MENU_OPENED,
	BOOK_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
	int entry_sel;
	int option_sel;
	int n_options;
} BookMenu;

void initBookMenu();
void openBookMenu();
void closeBookMenu();
int getBookMenuStatus();
void drawBookMenu();
void BookMenuCtrl();

void bookAgree();
void bookDisagree();

#endif