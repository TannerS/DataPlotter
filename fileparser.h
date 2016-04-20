#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "boost/filesystem/path.hpp"
#include "axis.h"
#include <QVector>

class FileParser
{
    public:

        QVector<double> processFile(boost::filesystem::path);

    private:
        void processString(std::string&, Axis&);
        void partialParse(std::string&);
};


#endif // FILEPARSER_H
