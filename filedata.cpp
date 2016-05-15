#include "filedata.h"
#include <algorithm>
#include <iostream>

// get file paths
std::vector<File> FileData::getPaths()
{
    return paths;
}
// set paths as one list at a time
void FileData::setPaths(std::vector<File> paths)
{
    this->paths = paths;
}
// add a single path to list
void FileData::addPath(File path)
{
    paths.push_back(path);
}
// reset paths to fix a problem
void FileData::pathReset()
{
    this->paths.clear();
}
// get size of list aka number of paths
size_t FileData::getNumberOfPaths()
{
    return paths.size();
}
// sort paths by timr
// this is needed for later when renaming
// the paths must be in order of time stamp
// since files can be read in any order
// the names won't be correct unless sorted
// by propery thing your renaming by
void FileData::sortByTime()
{
    // using std sort, pass in start and end of vector
    // and method to tell how to sort it
    std::sort(paths.begin(), paths.end(), FileCMP());
}
