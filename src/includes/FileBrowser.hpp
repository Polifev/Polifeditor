#pragma once
#include <string>
#include <vector>
#include <filesystem>

class FileBrowser {
	public:
		FileBrowser();
		void cd(std::string directory);
		std::string wd();
		std::vector<std::string> ls();
		//bool fileExists(std::string filename);
	
	private:
		std::filesystem::path _wd;
};