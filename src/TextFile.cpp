#include "TextFile.hpp"

#include <sstream>

/*
class TextFile {
	public:
		TextFile(std::string filename);
		void write();
		void read();
		std::string line(int line);
	private:
		std::string filename;
		std::string buffer;
};
*/

TextFile::TextFile(std::string filename) : filename{filename} 
{}

void TextFile::read(){
	// TODO read text file content
}

void TextFile::write() {
	// TODO write modified content to file
}

std::string TextFile::line(int line) {
	std::ostringstream out;  
	out << "line: " << line;
	return out.str();
}

int TextFile::lineCount() {
	return 10;
}