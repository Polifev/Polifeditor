#include "TextFile.hpp"

#include <locale>
#include <codecvt>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

TextFile::TextFile(std::string filename) : _filename{filename} 
{
	_lines.push_back("");
}

void TextFile::read(){
	_lines.clear();
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
	if(outFile){
		for(int i = 0; i < _lines.size() - 1; i++){
			outFile << _lines[i] << std::endl;
		}
		outFile << _lines[_lines.size() - 1];
	}
	outFile.close();
}

void TextFile::writeAs(std::string filename){
	_filename = filename;
	write();
}

int TextFile::lineCount() {
	return _lines.size();
}

void TextFile::insertLine(const int index){
	std::vector<std::string>::iterator it = _lines.begin() + index;
	_lines.insert(it, "");
}

void TextFile::editLine(int index, std::string newLine){
	if(_lines.size() > index && index >= 0){
		_lines[index] = newLine;
	}
	// Error
}

void TextFile::removeLine(int index){
	if(_lines.size() > index && index >= 0){
		std::vector<std::string>::iterator it = _lines.begin() + index;
		_lines.erase(it);
	}
	// Error
}

std::string TextFile::getLine(int index){
	return _lines[index];
}