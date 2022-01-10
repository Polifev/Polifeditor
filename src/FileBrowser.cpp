#include "FileBrowser.hpp"


FileBrowser::FileBrowser() : _wd{"./"} {
}

void FileBrowser::cd(std::string path){
	_wd = _wd / std::filesystem::path(path);
}

std::string FileBrowser::wd(){
	return _wd.string();
}

std::vector<std::string> FileBrowser::ls(){
	std::vector<std::string> result;
	for(const auto & entry : std::filesystem::directory_iterator(_wd)){
		result.push_back(entry.path().string());
	}
	return result;
}