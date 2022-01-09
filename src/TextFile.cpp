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
	_indentation.push_back(0);
}

void TextFile::read(){
	_lines.clear();
	_indentation.clear();
	
	std::ifstream inFile;

	inFile.open(_filename);
	if(! inFile) {
		// File cannot be opened ==> In-Memory buffer
	} else {
		std::string line;
		while(std::getline(inFile, line)){
			int indentation = 0;
			while(line[indentation] == '\t'){
				indentation++;
			}
			_indentation.push_back(indentation);
			_lines.push_back(line.substr(indentation));
		}
	}
	inFile.close();
}

void TextFile::write() {
	std::ofstream outFile;
	outFile.open(_filename);
	if(outFile){
		for(int i = 0; i < _lines.size() - 1; i++){
			for(int t = 0; t < _indentation[i]; t++){
				outFile << '\t';
			}
			outFile << _lines[i] << std::endl;
		}
		for(int t = 0; t < _indentation[_lines.size() - 1]; t++){
			outFile << '\t';
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
	_indentation.insert(_indentation.begin() + index, 0);
}

void TextFile::editLine(int index, std::string newLine){
	if(_lines.size() > index && index >= 0){
		_lines[index] = newLine;
	}
	// Error
}

void TextFile::setIndentation(int index, int indentation){
	if(_lines.size() > index && index >= 0){
		_indentation[index] = indentation;
	}
}

void TextFile::indentLine(int index){
	if(_lines.size() > index && index >= 0){
		_indentation[index] = _indentation[index] + 1;
	}
}

void TextFile::unindentLine(int index){
	if(_lines.size() > index && index >= 0){
		_indentation[index] = _indentation[index] - 1;
		if(_indentation[index] < 0){
			_indentation[index] = 0;
		}
	}
}

void TextFile::removeLine(int index){
	if(_lines.size() > index && index >= 0){
		_lines.erase(_lines.begin()+index);
		_indentation.erase(_indentation.begin()+index);
	}
	// Error
}

std::string TextFile::getLine(int index){
	return _lines[index];
}

int TextFile::getIndentation(int index){
	return _indentation[index];
}