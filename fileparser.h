#ifndef FILEPARSER_H
#define FILEPARSER_H

#include "boost/filesystem/path.hpp"
#include "axis.h"
#include <QVector>
#include "graph.h"
#include <QRunnable>
#include <QThread>
#include "file.h"

class FileParser : public QThread
{
    public:
        void processFiles();
        void storePaths(std::vector<File>);
        void stop();
        QVector<Graph> getGraphs();
        void run();
    private:
        void processString(std::string&, Axis&);
        void partialParse(std::string&);
        QVector<Graph> graphs;
        QVector<boost::filesystem::path> paths;


};


#endif // FILEPARSER_H
