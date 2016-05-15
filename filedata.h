#ifndef DATA_H
#define DATA_H

#include <vector>
#include "file.h"

class FileData
{
    // check .cpp file for more details
    public:
        std::vector<File> getPaths();
        void addPath(File path);
        size_t getNumberOfPaths();
        void sortByTime();
        void setPaths(std::vector<File>);
        void pathReset();
    private:
        std::vector<File> paths;
};

#endif // DATA_H


