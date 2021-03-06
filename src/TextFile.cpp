#include "TextFile.hpp"

#include "filesystem.hpp"
#include <locale>
#include <codecvt>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iterator>

TextFile::TextFile() : _filename{""}
{
	_lines.push_back("");
}

bool TextFile::readyToRead() {
	fs::path p = fs::path(_filename);
	return fs::exists(p) && !fs::is_directory(p);
}

void TextFile::read(){
	_lines.clear();
	std::ifstream inFile;

	inFile.open(_filename);
	if(! inFile) {
		// File cannot be opened ==> In-Memory buffer
	} else {
		std::string line;
		char c;
		int charint;
		while((charint = inFile.get()) != EOF){
			c = (char) charint;
			if(c == '\n'){
				_lines.push_back(line);
				line = std::string();
			} else {
				line.push_back(c);
			}
		}
		_lines.push_back(line);
	}
	inFile.close();
}

bool TextFile::readyToWrite(){
	fs::path p = fs::path(_filename);
	return p.has_filename();
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
	_lines.insert(_lines.begin() + index, "");
}

void TextFile::editLine(int index, std::string newLine){
	if(_lines.size() > index && index >= 0){
		_lines[index] = newLine;
	}
	// Error
}

void TextFile::removeLine(int index){
	if(_lines.size() > index && index >= 0){
		_lines.erase(_lines.begin()+index);
	}
	// Error
}

std::string TextFile::getLine(int index){
	return _lines[index];
}

void TextFile::filename(std::string filename){
	_filename = filename;
}

std::string TextFile::filename(){
	return _filename;
}
