#include "TextFile.hpp"

#include <ncurses.h>
#include <ctype.h>

#include <iostream>
#include <string>


#define CTRL_KEY(key) ((key) & 0x1f)

int main(int argc, char** argv) {
	TextFile file = TextFile("/home/pol/test.txt");

	initscr();
	noecho();

	WINDOW* top = subwin(stdscr, LINES / 2, COLS, 0, 0);
	WINDOW* bottom = subwin(stdscr, LINES / 2, COLS, LINES / 2, 0);

	box(top, ACS_VLINE, ACS_HLINE);
	box(bottom, ACS_VLINE, ACS_HLINE);

	bool exit = false;
	wmove(top, 1, 1);

	for(int i = 0; i < file.lineCount(); i++) {
		waddstr(bottom, file.line(i).c_str());
		waddch(bottom, '\n');
	}
	refresh();
	while(! exit) {
		char c = wgetch(top);
		if(iscntrl(c)){
			std::string formatStr = "%d";
			const char* format = formatStr.c_str();
			char buff[16];
			sprintf(buff, format, c);
			exit = ( c == CTRL_KEY('a') );
			waddstr(top, buff);
		} else {
			waddch(top, c);
		}
		refresh();
	}

	endwin();
	return 0;
}