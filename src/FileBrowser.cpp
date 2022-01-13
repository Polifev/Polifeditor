#include "FileBrowser.hpp"


FileBrowser::FileBrowser() : _wd{"./"} {
	_wd = fs::canonical(_wd);
}

void FileBrowser::cd(std::string path){
	_wd = fs::canonical(_wd / fs::path(path));
}

std::string FileBrowser::wd(){
	return _wd.string();
}

std::vector<std::string> FileBrowser::ls(){
	std::vector<std::string> result;
	for(const auto & entry : fs::directory_iterator(_wd)){
		result.push_back(entry.path().string());
	}
	return result;
}
