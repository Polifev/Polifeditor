#include "EditTextState.hpp"

#define NEW_LINE 10
#define BACK_SPACE 127
#define NO_CHAR 255
#define CTRL_KEY(key) ((key) & 0x1f)

AppState EditTextState::processInput(AppContext& context){
	context.editor()->renderFilePortion();
	context.editor()->refresh();
	std::string str = context.editor()->readMultibyteChar();
	
	//context.console()->show(str);
	//char buff[256];
	//sprintf(buff, "[%d]", str[0]);
	//context.console()->show(buff);

	AppState nextState = APPSTATE_EDIT;

	if(str.size() == 1){
		// MONO-BYTE characters handling
		char c = str[0];
		if(iscntrl(c)){
			switch (c) {
				case CTRL_KEY('x'):
					nextState = APPSTATE_EXIT;
					break;
				case CTRL_KEY('w'):
					nextState = APPSTATE_SAVE;
					break;
				case NEW_LINE:
					context.editor()->insertNewLine();
					break;
				case BACK_SPACE:
					context.editor()->eraseBackward();
					break;
				case '\t':
					context.editor()->indent();
					break;
				default :
					break;
			}
		} else {
			context.editor()->insertChar(c);
		}
	} else {
		// MULTI-BYTE character handling
		if(str[0] == 27){
			str = str.substr(1);
		}
		if(str == "[A"){ // UP
			context.editor()->move(-1, 0);
		} else if (str == "[B"){ // DOWN
			context.editor()->move(1, 0);
		} else if (str == "[C"){ // RIGHT
			context.editor()->move(0, 1);
		} else if (str == "[D"){ // LEFT
			context.editor()->move(0, -1);
		} else if (str == "[3~") { // DEL
			context.editor()->eraseForward();
		} else if (str == "[H") { // HOME
			context.editor()->move(0, -100000);
		} else if (str == "[1;5H") { // Ctrl+HOME
			context.editor()->move(-100000, -100000);
		} else if (str == "[F") { // END
			context.editor()->move(0, 100000);
		} else if (str == "[1;5F") { // Ctrl+END
			context.editor()->move(100000, 100000);
		} else if (str == "[Z") { // Shift+TAB
			context.editor()->unindent();
		} else {
			context.console()->show(str);
		}
	}
	return nextState;
}
