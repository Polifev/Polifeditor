#include "EditTextState.hpp"

#define NEW_LINE 10
#define BACK_SPACE 127
#define NO_CHAR 255
#define CTRL_KEY(key) ((key) & 0x1f)

AppState EditTextState::processInput(AppContext& context){
	//unsigned char c = context.editor()->readChar();
	std::string str = context.editor()->readMultibyteChar();
	if(str.size() == 1){
		unsigned char c = str[0];
		if(c == 255){
			// TimeoutChar
		} else if(iscntrl(c)){
			switch (c) {
				case CTRL_KEY('x'):
					return APPSTATE_EXIT;
					break;
				case CTRL_KEY('w'):
					//context.editor()->save();
					// TODO return APPSTATE_SAVE
					break;
				case NEW_LINE:
					context.editor()->insertNewLine();
					break;
				case BACK_SPACE:
					context.editor()->eraseBackward();
					break;
				default :
					break;
			}
		} else {
			context.editor()->insertChar(c);
		}
	} else {
		// Parse escape sequence
		if(str[0] == 27){
			str = str.substr(1);
		}
		if(str == "[A"){
			context.editor()->move(-1, 0);
		} else if (str == "[B"){
			context.editor()->move(1, 0);
		} else if (str == "[C"){
			context.editor()->move(0, 1);
		} else if (str == "[D"){
			context.editor()->move(0, -1);
		} else if (str == "[3~") {
			context.editor()->eraseForward();
		} else {
			context.console()->show(str);
		}
	}
	context.editor()->refresh();
	return APPSTATE_EDIT;
}
