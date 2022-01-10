#include "Keyboard.hpp"
#include <ncurses.h>

std::string Keyboard::readMultibyteChar(){
	int i = 0;
	char buffer[256];
	/*buffer[i++] = wgetch(_mainWindow);
	wtimeout(_mainWindow, 0);
	while((buffer[i++] = wgetch(_mainWindow)) != -1);
	buffer[i-1] = '\0';
	wtimeout(_mainWindow, -1);*/
	buffer[i++] = getch();
	timeout(0);
	while((buffer[i++] = getch()) != -1);
	buffer[i-1] = '\0';
	timeout(-1);
	return std::string(buffer);
}