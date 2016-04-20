#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "boost/filesystem/path.hpp"
#include "axis.h"

class FileParser
{
    public:
        void processFile(boost::filesystem::path);
        std::vector<Axis> getPoints();

    private:
        void processString(std::string&, Axis&);
        void partialParse(std::string&);
        std::vector<Axis> points;
};


#endif // FILEPARSER_H
