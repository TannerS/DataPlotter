#include "filedata.h"

FileData::FileData()
{
    this->paths = new std::vector<File>();
}

std::vector<File>* FileData::getPaths()
{
    return this->paths;
}

bool FileData::addPath(File path)
{
    paths->push_back(path);
    return true;
}

auto FileData::getNumberOfPaths()
{
    return paths->size();
}

FileData::~FileData()
{
    delete this->paths;
}



void FileData::sortByTime()
{
    //this->paths->s

    /*


http://stackoverflow.com/questions/1380463/sorting-a-vector-of-custom-objects

http://stackoverflow.com/questions/14081335/algorithm-vector-sort-with-objects









      */
}
