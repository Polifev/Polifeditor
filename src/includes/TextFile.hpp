#pragma once

#include <string>
#include <vector>

class TextFile {
	public:
		TextFile();
		void write();
		void writeAs(std::string filename);
		void read();
		int lineCount();
		void insertLine(int index);
		void editLine(int index, std::string newLine);
		void removeLine(int index);
		std::string getLine(int index);
		void filename(std::string filename);
		std::string filename();
	private:
		std::string _filename;
		std::vector<std::string> _lines;
};