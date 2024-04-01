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

#ifndef __CREDITS_H__
#define __CREDITS_H__

enum CreditsMenuStatus {
	CREDITS_MENU_CLOSED,
	CREDITS_MENU_CLOSING,
	CREDITS_MENU_OPENED,
	CREDITS_MENU_OPENING,
};

typedef struct {
	int status;
	float cur_pos;
	int entry_sel;
	int option_sel;
	int n_options;
} CreditsMenu;

void initCreditsMenu();
void openCreditsMenu();
void closeCreditsMenu();
int getCreditsMenuStatus();
void drawCreditsMenu();
void CreditsMenuCtrl();

#endif