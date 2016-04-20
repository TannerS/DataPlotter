#ifndef DATA_H
#define DATA_H

#include <vector>
#include "file.h"

class FileData
{
    public:
        std::vector<File> getPaths();
        bool addPath(File path);
        auto getNumberOfPaths();
        void sortByTime();
        void setPaths(std::vector<File>);
    private:
        std::vector<File> paths;
        //************************************************8
};

#endif // DATA_H


