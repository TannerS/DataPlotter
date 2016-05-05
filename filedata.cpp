#include "filedata.h"
#include <algorithm>
#include <iostream>

std::vector<File> FileData::getPaths()
{
    return paths;
}

void FileData::setPaths(std::vector<File> paths)
{
    this->paths = paths;
}

bool FileData::addPath(File path)
{
    paths.push_back(path);
    return true;
}

void FileData::pathReset()
{
    this->paths.clear();
}


auto FileData::getNumberOfPaths()
{
    return paths.size();
}

void FileData::sortByTime()
{
    std::sort(paths.begin(), paths.end(), FileCMP());
}
