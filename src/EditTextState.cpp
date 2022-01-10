#include "EditTextState.hpp"

#define NEW_LINE 10
#define BACK_SPACE 127
#define NO_CHAR 255
#define CTRL_KEY(key) ((key) & 0x1f)

AppState EditTextState::processInput(AppContext& context){
	char buffer[256];
	context.editor()->renderFile();
	context.editor()->refresh();
	std::string str = context.keyboard()->readMultibyteChar();
	
	//context.console()->display(str);
	//char buff[256];
	//sprintf(buff, "[%d]", str[0]);
	//context.console()->display(buff);

	AppState nextState = APPSTATE_EDIT;

	if(str.size() == 1){
		// MONO-BYTE characters handling
		char c = str[0];
		if(iscntrl(c)){
			switch (c) {
				case CTRL_KEY('x'):
					nextState = APPSTATE_EXIT;
					break;
				case CTRL_KEY('o'):
					nextState = APPSTATE_SAVE;
					break;
				case CTRL_KEY('l'):
					sprintf(buffer, "[Lin. %d; Col. %d]", context.editor()->getLineIndex(), context.editor()->getCharIndex());
					context.console()->display(buffer);
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
			context.editor()->moveUp();
		} else if (str == "[B"){ // DOWN
			context.editor()->moveDown();
		} else if (str == "[C"){ // RIGHT
			context.editor()->moveRight();
		} else if (str == "[D"){ // LEFT
			context.editor()->moveLeft();
		} else if (str == "[3~") { // DEL
			context.editor()->eraseForward();
		} else if (str == "[H") { // HOME
			context.editor()->moveToStartOfLine();
		} else if (str == "[1;5H") { // Ctrl+HOME
			context.editor()->moveToStartOfFile();
		} else if (str == "[F") { // END
			context.editor()->moveToEndOfLine();
		} else if (str == "[1;5F") { // Ctrl+END
			context.editor()->moveToEndOfFile();
		} else {
			context.console()->display(str);
		}
	}
	return nextState;
}
