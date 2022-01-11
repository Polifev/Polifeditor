#pragma once

#include <string>
#include <vector>

class TextFile {
	public:
		TextFile();
		void filename(std::string filename);
		std::string filename();

		bool readyToWrite();
		void write();
		void writeAs(std::string filename);

		bool readyToRead();
		void read();

		int lineCount();
		std::string getLine(int index);
		void insertLine(int index);
		void editLine(int index, std::string newLine);
		void removeLine(int index);
	private:
		std::string _filename;
		std::vector<std::string> _lines;
};
