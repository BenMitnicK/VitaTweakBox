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
#include "utils.h"
#include "help.h"
#include "theme.h"
#include "language.h"

static int n_Help_entries = 0;
static HelpMenu helpmenu;

static int help;

void initHelpMenu() {
	memset(&helpmenu, 0, sizeof(HelpMenu));
	helpmenu.status = HELP_MENU_CLOSED;
	n_Help_entries = 1;	
}

void openHelpMenu(int number) {
	help = number;
	helpmenu.status = HELP_MENU_OPENING;
}

void closeHelpMenu() {
	helpmenu.status = HELP_MENU_CLOSING;
}

int getHelpMenuStatus() {
	return helpmenu.status;
}

void helpBrowser(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_circle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_select); // 47
	
	vita2d_draw_texture(help_circle, HELP_BROWSER_CIRCLE_X, y+HELP_BROWSER_CIRCLE_Y);
	pgf_draw_text(icon_width+HELP_BROWSER_CIRCLE_TEXT_X, y+HELP_BROWSER_CIRCLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_CIRCLE]);
	vita2d_draw_texture(help_cross, HELP_BROWSER_CROSS_X, y+HELP_BROWSER_CROSS_Y);
	pgf_draw_text(icon_width+HELP_BROWSER_CROSS_TEXT_X, y+HELP_BROWSER_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_CROSS]);
	
	vita2d_draw_texture(help_square, HELP_BROWSER_SQUARE_X, y+HELP_BROWSER_SQUARE_Y);
	pgf_draw_text(icon_width+HELP_BROWSER_SQUARE_TEXT_X, y+HELP_BROWSER_SQUARE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_SQUARE]);
	vita2d_draw_texture(help_triangle, HELP_BROWSER_TRIANGLE_X, y+HELP_BROWSER_TRIANGLE_Y);
	pgf_draw_text(icon_width+HELP_BROWSER_TRIANGLE_TEXT_X, y+HELP_BROWSER_TRIANGLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_TRIANGLE]);
	
	vita2d_draw_texture(help_select, HELP_BROWSER_SELECT_X, y+HELP_BROWSER_SELECT_Y);
	pgf_draw_text(icon2_width+HELP_BROWSER_SELECT_TEXT_X, y+HELP_BROWSER_SELECT_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_SELECT]);
	/*vita2d_draw_texture(help_start, HELP_BROWSER_START_X, y+HELP_BROWSER_START_Y);
	pgf_draw_text(icon2_width+HELP_BROWSER_START_TEXT_X, y+HELP_BROWSER_START_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BROWSER_START]);*/
	
}

void helpTextEditor(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_circle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_lr); // 50
	
	vita2d_draw_texture(help_circle, HELP_TEXTEDITOR_CIRCLE_X, y+HELP_TEXTEDITOR_CIRCLE_Y);
	pgf_draw_text(icon_width+HELP_TEXTEDITOR_CIRCLE_TEXT_X, y+HELP_TEXTEDITOR_CIRCLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_CIRCLE]);
	vita2d_draw_texture(help_cross, HELP_TEXTEDITOR_CROSS_X, y+HELP_TEXTEDITOR_CROSS_Y);
	pgf_draw_text(icon_width+HELP_TEXTEDITOR_CROSS_TEXT_X, y+HELP_TEXTEDITOR_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_CROSS]);
	
	vita2d_draw_texture(help_square, HELP_TEXTEDITOR_SQUARE_X, y+HELP_TEXTEDITOR_SQUARE_Y);
	pgf_draw_text(icon_width+HELP_TEXTEDITOR_SQUARE_TEXT_X, y+HELP_TEXTEDITOR_SQUARE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_SQUARE]);
	vita2d_draw_texture(help_triangle, HELP_TEXTEDITOR_TRIANGLE_X, y+HELP_TEXTEDITOR_TRIANGLE_Y);
	pgf_draw_text(icon_width+HELP_TEXTEDITOR_TRIANGLE_TEXT_X, y+HELP_TEXTEDITOR_TRIANGLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_TRIANGLE]);
	
	vita2d_draw_texture(help_pad, HELP_TEXTEDITOR_PAD_X, y+HELP_TEXTEDITOR_PAD_Y);
	pgf_draw_text(icon_width+HELP_TEXTEDITOR_PAD_TEXT_X, y+HELP_TEXTEDITOR_PAD_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_PAD]);
	vita2d_draw_texture(help_lr, HELP_TEXTEDITOR_LR_X, y+HELP_TEXTEDITOR_LR_Y);
	pgf_draw_text(icon2_width+HELP_TEXTEDITOR_LR_TEXT_X, y+HELP_TEXTEDITOR_LR_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_TEXTEDITOR_LR]);
	
}

void helpHexEditor(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_circle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_lr); // 50
	
	vita2d_draw_texture(help_circle, HELP_HEXEDITOR_CIRCLE_X, y+HELP_HEXEDITOR_CIRCLE_Y);
	pgf_draw_text(icon_width+HELP_HEXEDITOR_CIRCLE_TEXT_X, y+HELP_HEXEDITOR_CIRCLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_HEXEDITOR_CIRCLE]);
	vita2d_draw_texture(help_cross, HELP_HEXEDITOR_CROSS_X, y+HELP_HEXEDITOR_CROSS_Y);
	pgf_draw_text(icon_width+HELP_HEXEDITOR_CROSS_TEXT_X, y+HELP_HEXEDITOR_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_HEXEDITOR_CROSS]);
	
	vita2d_draw_texture(help_square, HELP_HEXEDITOR_SQUARE_X, y+HELP_HEXEDITOR_SQUARE_Y);
	pgf_draw_text(icon_width+HELP_HEXEDITOR_SQUARE_TEXT_X, y+HELP_HEXEDITOR_SQUARE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_HEXEDITOR_SQUARE]);
	vita2d_draw_texture(help_lr, HELP_HEXEDITOR_LR_X, y+HELP_HEXEDITOR_LR_Y);
	pgf_draw_text(icon2_width+HELP_HEXEDITOR_LR_TEXT_X, y+HELP_HEXEDITOR_LR_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_HEXEDITOR_LR]);
	
}

void helpPhotoViewer(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_circle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_lr); // 47
	
	vita2d_draw_texture(help_circle, HELP_PHOTOVIEWER_CIRCLE_X, y+HELP_PHOTOVIEWER_CIRCLE_Y);
	pgf_draw_text(icon_width+HELP_PHOTOVIEWER_CIRCLE_TEXT_X, y+HELP_PHOTOVIEWER_CIRCLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_PHOTOVIEWER_CIRCLE]);
	vita2d_draw_texture(help_pad, HELP_PHOTOVIEWER_PAD_X, y+HELP_PHOTOVIEWER_PAD_Y);
	pgf_draw_text(icon_width+HELP_PHOTOVIEWER_PAD_TEXT_X, y+HELP_PHOTOVIEWER_PAD_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_PHOTOVIEWER_PAD]);
	
	vita2d_draw_texture(help_cross, HELP_PHOTOVIEWER_CROSS_X, y+HELP_PHOTOVIEWER_CROSS_Y);
	pgf_draw_text(icon_width+HELP_PHOTOVIEWER_CROSS_TEXT_X, y+HELP_PHOTOVIEWER_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_PHOTOVIEWER_CROSS_R]);
	vita2d_draw_texture(help_r_analog, HELP_PHOTOVIEWER_R_ANALOG_X, y+HELP_PHOTOVIEWER_R_ANALOG_Y);
	pgf_draw_text(icon_width+HELP_PHOTOVIEWER_R_ANALOG_TEXT_X, y+HELP_PHOTOVIEWER_R_ANALOG_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_PHOTOVIEWER_CROSS_R]);
	
	vita2d_draw_texture(help_lr, HELP_PHOTOVIEWER_LR_X, y+HELP_PHOTOVIEWER_LR_Y);
	pgf_draw_text(icon2_width+HELP_PHOTOVIEWER_LR_TEXT_X, y+HELP_PHOTOVIEWER_LR_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_PHOTOVIEWER_LR]);
	
}

void helpAudioPlayer(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_circle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_lr); // 47
	
	vita2d_draw_texture(help_circle, HELP_AUDIOPLAYER_CIRCLE_X, y+HELP_AUDIOPLAYER_CIRCLE_Y);
	pgf_draw_text(icon_width+HELP_AUDIOPLAYER_CIRCLE_TEXT_X, y+HELP_AUDIOPLAYER_CIRCLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_AUDIOPLAYER_CIRCLE]);
	vita2d_draw_texture(help_cross, HELP_AUDIOPLAYER_CROSS_X, y+HELP_AUDIOPLAYER_CROSS_Y);
	pgf_draw_text(icon_width+HELP_AUDIOPLAYER_CROSS_TEXT_X, y+HELP_AUDIOPLAYER_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_AUDIOPLAYER_CROSS]);
	
	vita2d_draw_texture(help_triangle, HELP_AUDIOPLAYER_TRIANGLE_X, y+HELP_AUDIOPLAYER_TRIANGLE_Y);
	pgf_draw_text(icon_width+HELP_AUDIOPLAYER_TRIANGLE_TEXT_X, y+HELP_AUDIOPLAYER_TRIANGLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_AUDIOPLAYER_TRIANGLE]);
	vita2d_draw_texture(help_pad, HELP_AUDIOPLAYER_PAD_X, y+HELP_AUDIOPLAYER_PAD_Y);
	pgf_draw_text(icon_width+HELP_AUDIOPLAYER_PAD_TEXT_X, y+HELP_AUDIOPLAYER_PAD_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_AUDIOPLAYER_PAD]);
	
	vita2d_draw_texture(help_lr, HELP_AUDIOPLAYER_LR_X, y+HELP_AUDIOPLAYER_LR_Y);
	pgf_draw_text(icon2_width+HELP_AUDIOPLAYER_LR_TEXT_X, y+HELP_AUDIOPLAYER_LR_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_AUDIOPLAYER_LR]);
	
}

void helpBookViewer(){
	
	float y = 65 - helpmenu.cur_pos;
	unsigned int icon_width = vita2d_texture_get_width(help_triangle); // 25
	unsigned int icon2_width = vita2d_texture_get_width(help_lr); // 47
	
	vita2d_draw_texture(help_triangle, HELP_BOOK_TRIANGLE_X, y+HELP_BOOK_TRIANGLE_Y);
	pgf_draw_text(icon_width+HELP_BOOK_TRIANGLE_TEXT_X, y+HELP_BOOK_TRIANGLE_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BOOK_TRIANGLE]);
	vita2d_draw_texture(help_pad, HELP_BOOK_PAD_X, y+HELP_BOOK_PAD_Y);
	pgf_draw_text(icon_width+HELP_BOOK_PAD_TEXT_X, y+HELP_BOOK_PAD_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BOOK_PAD]);
	
	vita2d_draw_texture(help_cross, HELP_BOOK_CROSS_X, y+HELP_BOOK_CROSS_Y);
	pgf_draw_text(icon_width+HELP_BOOK_CROSS_TEXT_X, y+HELP_BOOK_CROSS_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BOOK_CROSS_R]);
	vita2d_draw_texture(help_r_analog, HELP_BOOK_R_ANALOG_X, y+HELP_BOOK_R_ANALOG_Y);
	pgf_draw_text(icon_width+HELP_BOOK_R_ANALOG_TEXT_X, y+HELP_BOOK_R_ANALOG_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BOOK_CROSS_R]);
	
	vita2d_draw_texture(help_lr, HELP_BOOK_LR_X, y+HELP_BOOK_LR_Y);
	pgf_draw_text(icon2_width+HELP_BOOK_LR_TEXT_X, y+HELP_BOOK_LR_TEXT_Y, HELP_MENU_ITEM_COLOR, language_container[HELP_BOOK_LR]);
	
}

void drawHelpMenu() {
	if (helpmenu.status == HELP_MENU_CLOSED)
		return;

	// Closing settings menu
	if (helpmenu.status == HELP_MENU_CLOSING) {
		if (helpmenu.cur_pos > 0.0f) {
			helpmenu.cur_pos -= easeOut(0.0f, helpmenu.cur_pos, 0.25f, 0.01f);
		} else {
			helpmenu.status = HELP_MENU_CLOSED;
		}
	}

	// Opening settings menu
	if (helpmenu.status == HELP_MENU_OPENING) {
		if (helpmenu.cur_pos < SCREEN_HEIGHT) {
			helpmenu.cur_pos += easeOut(helpmenu.cur_pos, 65, 0.25f, 0.01f);
		} else {
			helpmenu.status = HELP_MENU_OPENED;
		}
	}
	
	if (!help_image) {
	help_image = vita2d_create_empty_texture(SCREEN_WIDTH, SCREEN_HEIGHT);
		void *data = vita2d_texture_get_datap(help_image);

		int y;
		for (y = 0; y < SCREEN_HEIGHT; y++) {
			int x;
			for (x = 0; x < SCREEN_WIDTH; x++) {
				((uint32_t *)data)[x + SCREEN_WIDTH * y] = HELP_MENU_COLOR;
			}
		}
	}
	
	// Draw help menu
	vita2d_draw_texture(help_image, 0.0f, SCREEN_HEIGHT - helpmenu.cur_pos);
    
	switch (help){
		case 1:
		helpBrowser();
		break;
		case 2:
		helpTextEditor();
		break;
		case 3:
		helpHexEditor();
		break;
		case 4:
		helpPhotoViewer();
		break;
		case 5:
		helpAudioPlayer();
		break;
		case 6:
		helpBookViewer();
		break;
	}

}

void HelpMenuCtrl() {
	
	// Close
	if (pressed_pad[PAD_START]) {
		closeHelpMenu();
	}
}
