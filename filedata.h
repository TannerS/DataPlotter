#ifndef DATA_H
#define DATA_H

#include <vector>
#include "file.h"

class FileData
{
    public:
        FileData();
        std::vector<File>* getPaths();
        bool addPath(File path);
        auto getNumberOfPaths();
        ~FileData();

    private:
        std::vector<File>* paths;
        //************************************************8
        void sortByTime();
};

#endif // DATA_H


