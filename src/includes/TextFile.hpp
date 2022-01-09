#pragma once

#include <string>
#include <vector>

class TextFile {
	public:
		TextFile(std::string filename);
		void write();
		void writeAs(std::string filename);
		void read();

		int lineCount();
		void insertLine(int index);
		void editLine(int index, std::string newLine);
		void indentLine(int index);
		void unindentLine(int index);
		void removeLine(int index);
		std::string getLine(int index);
		int getIndentation(int index);
		void setIndentation(int index, int indentation);
	private:
		std::string _filename;
		std::vector<std::string> _lines;
		std::vector<int> _indentation;
};