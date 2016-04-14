#ifndef FILENAMES_H
#define FILENAMES_H

#include <vector>

class FileNames
{
    public:
        FileNames();
        void getFileNames();
        // need function to get names from in vector
        ~FileNames();

    private:
        const std::string settings_name;
        std::vector<std::string> names;
    };

#endif // FILENAMES_H
