#pragma once
#include "filesystem.hpp"

#include <string>
#include <vector>

class FileBrowser {
	public:
		FileBrowser();
		void cd(std::string directory);
		std::string wd();
		std::vector<std::string> ls();
		//bool fileExists(std::string filename);
	private:
		fs::path _wd;
};
