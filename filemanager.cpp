#include "filemanager.h"
#include <dirent.h>
#include <errno.h>
#include <cstring>

using namespace std;

size_t FileManager::find_ext_idx(const char* fileName) {
    size_t len = strlen(fileName);
    size_t idx = len-1;
    for(size_t i = 0; *(fileName+i); i++) {
        if (*(fileName+i) == '.') {
            idx = i;
        } else if (*(fileName + i) == '/' || *(fileName + i) == '\\') {
            idx = len - 1;
        }
    }
    return idx+1;
}

std::string FileManager::get_file_ext(const char* fileName) {
    return std::string(fileName).substr(find_ext_idx(fileName));
}


FileManager::FileManager(const char* filename) {
    _filesImages = std::vector<std::string>();
    DIR *dp;
    char* extension = "jpg";
    struct dirent *dirp;
    if((dp = opendir(filename)) == NULL) {
        cout << "Error(" << errno << ") opening " << filename << endl;
    }

    while ((dirp = readdir(dp)) != NULL) {
        string name = string(dirp->d_name);
        if(name != "." && name != "..") {
            if(extension == get_file_ext(name.c_str())) {
                _filesImages.push_back("data/"+name);
            } else {
                _filesISO.push_back("data/"+name);
            }
        }
    }
    closedir(dp);
}


void FileManager::displayFiles() {
    for (unsigned int i = 0; i < _filesImages.size(); ++i) {
        cout << _filesImages[i] << endl;
    }
}


std::vector<std::string> FileManager::getFilesImages() {
    return _filesImages;
}

std::vector<std::string> FileManager::getFilesISOs() {
    return _filesISO;
}

