#include "vitabackup.h"

#include "../main.h"

SceVoid ProgressBar_DisplayProgress(char *msg, char *src, SceULong64 offset, SceULong64 size)
{
	vita2d_start_drawing();
	vita2d_clear_screen();
	
	int title_width = vita2d_pgf_text_width(font, 1.5f, msg);
	pgf2_draw_text((960 - title_width) / 2, 50, WHITE, 1.5f, msg);

	int name_width = vita2d_pgf_text_width(font, 1.5f, src);
	pgf2_draw_text(((960 - name_width) / 2), 270, WHITE, 1.5f, src);

	vita2d_draw_rectangle(200, 300, 560, 30, GREEN);
	vita2d_draw_rectangle(200, 300, offset / size * 560.0, 30, GREEN);

	vita2d_end_frame();
}