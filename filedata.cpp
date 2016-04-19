#include "filedata.h"
#include <algorithm>
#include <iostream>

FileData::FileData()
{
    //this->paths = new std::vector<File>();
}

std::vector<File> FileData::getPaths()
{
    return paths;
}

void FileData::setPaths(std::vector<File> paths)
{

    std::vector<File>::iterator i;

    for(i = paths.begin(); i != paths.end(); ++i)
    {
        std::cout << "DEBUG _____: " << (*i).path << std::endl;

}




    this->paths = paths;



    std::vector<File>::iterator ii;

    for(ii = this->paths.begin(); ii != this->paths.end(); ++ii)
    {
        std::cout << "DEBUG _____: " << (*ii).path << std::endl;

}




}

bool FileData::addPath(File path)
{
    paths.push_back(path);
    return true;
}

auto FileData::getNumberOfPaths()
{
    return paths.size();
}

FileData::~FileData()
{
   // delete this->paths;
}

void FileData::sortByTime()
{
    // FIND ALTER SOLUTION************************************
    std::sort(paths.begin(), paths.end(), FileCMP());
    // http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects
    // http://stackoverflow.com/questions/14081335/algorithm-vector-sort-with-objects
}
