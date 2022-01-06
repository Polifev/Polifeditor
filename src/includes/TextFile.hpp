#pragma once

#include <string>

class TextFile {
	public:
		TextFile(std::string filename);
		void write();
		void read();

		std::string line(int line);
		int lineCount();
	private:
		std::string filename;
		std::string buffer;
};