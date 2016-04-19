#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "axis.h"

class FileParser
{
    public:
        FileParser();
        std::vector<Axis> processFile();


    private:
        Axis processString();


};








#endif // FILEPARSER_H
