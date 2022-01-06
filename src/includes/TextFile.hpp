#pragma once

#include <string>
#include <vector>

class TextFile {
	public:
		TextFile(std::string filename);
		void write();
		void read();

		void insertLine(int index);
		void editLine(int index, std::string newLine);
		std::string getLine(int index);
	private:
		std::string _filename;
		std::string _buffer;
		std::vector<std::string> _lines;
};