#include "apilib.h"

#define WIN_W 30
#define WIN_H 15

struct FileInfo {
	char name[13];
	char ext[4];
	int size;
};

struct FileInfo file_list[] = {
	{"A", "HRB", 1234},
	{"HELLO3", "HRB", 5678},
	{"HELLO4", "HRB", 9012},
	{"HELLO5", "HRB", 3456},
	{"WINHELO", "HRB", 7890},
	{"WINHELO2", "HRB", 2345},
	{"WINHELO3", "HRB", 6789},
	{"STAR1", "HRB", 1234},
	{"STARS", "HRB", 5678},
	{"STARS2", "HRB", 9012},
	{"LINES", "HRB", 3456},
	{"WALK", "HRB", 7890},
	{"NOODLE", "HRB", 2345},
	{"BEEPDOWN", "HRB", 6789},
	{"COLOR", "HRB", 1234},
	{"COLOR2", "HRB", 5678},
	{"SOSU", "HRB", 9012},
	{"SOSU2", "HRB", 3456},
	{"SOSU3", "HRB", 7890},
	{"TYPE", "HRB", 2345},
	{"IROHA", "HRB", 6789},
	{"CHKLANG", "HRB", 1234},
	{"NOTREC", "HRB", 5678},
	{"BBALL", "HRB", 9012},
	{"INVADER", "HRB", 3456},
	{"CALC", "HRB", 7890},
	{"TVIEW", "HRB", 2345},
	{"MMLPLAY", "HRB", 6789},
	{"GVIEW", "HRB", 1234},
	{"FILEMGR", "HRB", 1901},
	{"KIRAKIRA", "MML", 5000},
	{"FUJISAN", "MML", 6000},
	{"DAIGO", "MML", 7000},
	{"DAIKU", "MML", 8000},
	{"FUJISAN", "JPG", 10000},
	{"NIGHT", "BMP", 15000},
	{"EUC", "TXT", 2000},
	{"", "", 0}
};

void draw_file_list(int win, int file_count, int selected);
void run_file(char *name, char *ext);
int sprintf(char *str, const char *fmt, ...);

void HariMain(void)
{
	char *winbuf;
	int win, selected = 0;
	int file_count = 0;
	int key;

	api_initmalloc();
	winbuf = api_malloc(240 * 240);
	if (!winbuf) {
		api_putstr0("Memory allocation failed\n");
		api_end();
	}

	win = api_openwin(winbuf, 240, 240, -1, "FileMgr");
	api_boxfilwin(win, 0, 0, 239, 239, 7);
	api_boxfilwin(win, 0, 0, 239, 29, 1);

	// 计算文件数量
	while (file_list[file_count].name[0] != 0) {
		file_count++;
	}

	// 显示文件数量
	char msg[20];
	sprintf(msg, "Files: %d\n", file_count);
	api_putstr0(msg);

	for (;;) {
		draw_file_list(win, file_count, selected);

		key = api_getkey(1);
		
		if (key == 'Q' || key == 'q') {
			api_end();
		}

		if (key == 0x1b) {
			api_end();
		}

		if (key == 0x0d) {
			if (file_count > 0) {
				run_file(file_list[selected].name, file_list[selected].ext);
			}
		}

		if (key == 0x28) {
			selected++;
			if (selected >= file_count) {
				selected = file_count - 1;
			}
		}

		if (key == 0x26) {
			selected--;
			if (selected < 0) {
				selected = 0;
			}
		}

		if (key == 0x21) {
			selected -= WIN_H - 2;
			if (selected < 0) {
				selected = 0;
			}
		}

		if (key == 0x22) {
			selected += WIN_H - 2;
			if (selected >= file_count) {
				selected = file_count - 1;
			}
		}
	}
}

void draw_file_list(int win, int file_count, int selected)
{
	int i, idx;
	char s[30];
	int bg_col, fg_col;

	api_boxfilwin(win, 0, 30, 239, 239, 7);

	for (i = 0; i < WIN_H - 2; i++) {
		idx = selected - (WIN_H / 2) + i + 1;
		if (idx < 0 || idx >= file_count) {
			continue;
		}

		if (idx == selected) {
			bg_col = 1;
			fg_col = 7;
		} else {
			bg_col = 7;
			fg_col = 0;
		}

		api_boxfilwin(win, 0, 30 + i * 16, 239, 30 + i * 16 + 15, bg_col);

		if (file_list[idx].ext[0] != 0) {
			sprintf(s, "%s.%s %7d", file_list[idx].name, file_list[idx].ext, file_list[idx].size);
		} else {
			sprintf(s, "%s       %7d", file_list[idx].name, file_list[idx].size);
		}
		api_putstrwin(win, 8, 30 + i * 16 + 4, fg_col, 20, s);
	}

	api_refreshwin(win, 0, 0, 240, 240);
}

void run_file(char *name, char *ext)
{
	char cmdline[30];
	int fh;

	if (ext[0] == 'H' && ext[1] == 'R' && ext[2] == 'B') {
		sprintf(cmdline, "%s.HRB", name);
		api_putstr0("Starting ");
		api_putstr0(cmdline);
		api_putstr0("...\n");
		fh = api_fopen(cmdline);
		if (fh == 0) {
			api_putstr0("File not found.\n");
			return;
		}
		api_fclose(fh);
		api_putstr0("Use console to run: ");
		api_putstr0(name);
		api_putstr0("\n");
	} else if (ext[0] == 'M' && ext[1] == 'M' && ext[2] == 'L') {
		api_putstr0("Use mmlplay to play: ");
		api_putstr0(name);
		api_putstr0(".MML\n");
	} else if (ext[0] == 'J' && ext[1] == 'P' && ext[2] == 'G') {
		api_putstr0("Use gview to view: ");
		api_putstr0(name);
		api_putstr0(".JPG\n");
	} else if (ext[0] == 'B' && ext[1] == 'M' && ext[2] == 'P') {
		api_putstr0("Use gview to view: ");
		api_putstr0(name);
		api_putstr0(".BMP\n");
	} else {
		api_putstr0("Unknown file type: ");
		api_putstr0(ext);
		api_putstr0("\n");
	}
}
