#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "boost/filesystem/path.hpp"
#include "axis.h"
#include <QVector>
#include "graph.h"

class FileParser
{
    public:

        Graph processFile(boost::filesystem::path);


    private:
        void processString(std::string&, Axis&);
        void processString(std::string&, float&);
        void partialParse(std::string&);
        void parseTime(std::string&);
};


#endif // FILEPARSER_H
