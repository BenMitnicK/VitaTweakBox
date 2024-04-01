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

#include "main.h"
#include "init.h"
#include "utils.h"
#include "credits.h"
#include "theme.h"
#include "touch.h"

static int n_Credits_entries = 0;
static CreditsMenu creditsmenu;

void initCreditsMenu() {
	memset(&creditsmenu, 0, sizeof(CreditsMenu));
	creditsmenu.status = CREDITS_MENU_CLOSED;
	n_Credits_entries = 1;	
}

void openCreditsMenu() {
	creditsmenu.status = CREDITS_MENU_OPENING;
}

void closeCreditsMenu() {
	creditsmenu.status = CREDITS_MENU_CLOSING;
}

int getCreditsMenuStatus() {
	return creditsmenu.status;
}

void drawCreditsMenu() {
	if (creditsmenu.status == CREDITS_MENU_CLOSED)
		return;

	// Closing settings menu
	if (creditsmenu.status == CREDITS_MENU_CLOSING) {
		if (creditsmenu.cur_pos > 0.0f) {
			creditsmenu.cur_pos -= easeOut(0.0f, creditsmenu.cur_pos, 0.25f, 0.01f);
		} else {
			creditsmenu.status = CREDITS_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (creditsmenu.status == CREDITS_MENU_OPENING) {
		if (creditsmenu.cur_pos < SCREEN_HEIGHT) {
			creditsmenu.cur_pos += easeOut(creditsmenu.cur_pos, SCREEN_HEIGHT, 0.25f, 0.01f);
		} else {
			creditsmenu.status = CREDITS_MENU_OPENED;
		}
	}
	
	// Draw credits menu
	vita2d_draw_texture(credit_image, 229, creditsmenu.cur_pos - 420);

}

void CreditsMenuCtrl() {
	TouchFront_Update();
	TouchBack_Update();
	
	// Close
	if (pressed_pad[PAD_CANCEL]) {
		closeCreditsMenu();
	}else if (TouchFront_CheckIsPressed()) 
	{
		if (!(TouchFront_GetX() >= 229 && TouchFront_GetX() <= 731 && TouchFront_GetY() >= 124 && TouchFront_GetY() <= 420))
			closeCreditsMenu();
	}
}