#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <vector>

class FileManager {
    public:
        FileManager(const char* filename);
        void displayFiles();
        std::vector<std::string> getFilesImages();
        std::vector<std::string> getFilesISOs();
        size_t find_ext_idx(const char* fileName);
        std::string get_file_ext(const char* fileName);
    private:
        std::vector<std::string> _filesImages;
        std::vector<std::string> _filesISO;
};

#endif // FILEMANAGER_H
