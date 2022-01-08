#include "TextFile.hpp"
#include "Editor.hpp"

#include <ncurses.h>
#include <ctype.h>

#include <iostream>
#include <sstream>
#include <string>

#define NEW_LINE 10
#define BACK_SPACE 127
#define NO_CHAR 255
#define CTRL_KEY(key) ((key) & 0x1f)

void escaped(Editor &editor, char c);

//void printInConsole(WINDOW* console, std::string str);

int COUNTER = 0;

int main(int argc, char** argv) {
	Editor editor;
	
	if(argc > 1){
		editor.openTextFile(argv[1]);
	}
	
	editor.renderFilePortion(0);
	editor.moveTo(0, 0);

	bool exit = false;
	bool escape = false;
	bool bracket = false;
	while(! exit) {
		std::string mc = editor.readMultibyteChar();
		editor.printToConsole(mc);
		continue;
		
		unsigned char c = editor.readChar();
		
		char buff[32];
		
		//sprintf(buff, "[%d]", ++COUNTER);
		sprintf(buff, "[%d]", (int) sizeof(wchar_t));
		//editor.printToConsole(buff);

		if(c == 255){
			// TimeoutChar
		}
		else if(! escape && c == 27){
			escape = true;
		}
		else if(escape && !bracket && c == '['){
			bracket = true;
		}
		else if(escape && bracket){
			escape = false;
			bracket = false;
			escaped(editor, c);
		} else if(iscntrl(c)){
			switch (c) {
				case CTRL_KEY('x'):
					exit = true;
					break;
				case CTRL_KEY('w'):
					editor.save();
					break;
				case NEW_LINE:
					editor.insertNewLine();
					break;
				case BACK_SPACE:
					editor.eraseBackward();
					break;
				default :
					std::ostringstream output;
					output << (int) c;
					//editor.printToConsole(output.str());
					break;
			}
		} else {
			editor.insertChar(c);
		}
		editor.refresh();
	}

	editor.dispose();
	return 0;
}

void escaped(Editor& editor, char c) {
	switch(c) {
		case 'A':
			// UP
			editor.move(-1, 0);
			break;
		case 'B':
			// DOWN
			editor.move(1, 0);
			break;
		case 'C':
			// RIGHT
			editor.move(0, 1);
			break;
		case 'D':
			// LEFT
			editor.move(0, -1);
			break;
		default:
			break;
	}
}
