#ifndef FILENAMES_H
#define FILENAMES_H

#include <vector>
#include <unordered_map>

class FileNames
{
    public:
        FileNames();
        void loadSettings();
        std::string getMapValue(std::string);
        // need function to get names from in vector
        ~FileNames();

    private:
        const std::string settings_name;
        std::unordered_map<std::string, std::string> names;
    };

#endif // FILENAMES_H
