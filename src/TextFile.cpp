#include "TextFile.hpp"

#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

TextFile::TextFile(std::string filename) : _filename{filename} 
{}

void TextFile::read(){
	std::ifstream inFile;

	inFile.open(_filename);
	if(! inFile) {
		// File cannot be opened ==> In-Memory buffer
	} else {
		std::string line;
		while(std::getline(inFile, line)){
			_lines.push_back(line);
		}
	}
	inFile.close();
}

void TextFile::write() {
	std::ofstream outFile;
	outFile.open(_filename);

	for(const std::string &line: _lines){
		outFile << line << std::endl;
	}
	outFile.close();
}

void TextFile::insertLine(const int index){
	std::vector<std::string>::iterator it = _lines.begin() + index;
	_lines.insert(it, std::string(""));
}

void TextFile::editLine(int index, std::string newLine){
	if(_lines.size() > index){
		_lines[index] = newLine;
	}
	// Error
}

std::string TextFile::getLine(int index){
	return _lines[index];
}