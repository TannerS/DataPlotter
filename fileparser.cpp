#include "fileparser.h"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/fstream.hpp"
#include "axis.h"
#include <sstream>
#include "graph.h"
#include <QMessageBox>

// process file to get axis from
Graph* FileParser::processFile(boost::filesystem::path path)
{
    // temp path with removed ext
    boost::filesystem::path temp_path(path);
    // create stream to open file
    boost::filesystem::fstream in;
    // open file using path
    in.open(temp_path, std::ios::in);
    // remove ext so later we can use filename for photo name without the .xxx
    temp_path.replace_extension(".png");
    // temp Axis to pass between methods and set in graph object
    Axis xy;
    // temp graph
    Graph* graph = new Graph();
    // set filename
    graph->setFileName(QString::fromStdString(temp_path.string()));
    // error
    if (in.fail())
    {
        // error message
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Failed to parse file at it's location");
        messageBox.setFixedSize(500,200);
    }
    // used to skip not needed lines
    int counter = 0;
    // used to get x,y min,max
    float xmin = 0, ymin = 0, xmax = 0, ymax = 0;
    // temp string to hold file
    std::string temp = "";
    // prase each file line
    while (getline(in, temp))
    {
        // if the line is the time
        if(counter == 11)
            // get the time
            graph->setTime(temp);
        // if we are reading the data part of the file
        if(counter > 14)
        {
            // process string to get xy axis
            processString(temp, xy);
            // get x,y coordinates
            graph->setXAxisVectorPoint(xy.x);
            graph->setYAxisVectorPoint(xy.y);
            // first real line of data
            if(counter == 15)
            {
                // set up default min and max as the firts value
                xmin = xmax = xy.x;
                ymin = ymax = xy.y;
                // one more so it does not enter this if statement agian
                counter++;
            }
            else
            {
                //compare to find min and max for each x and y
                if(xy.x < xmin)
                    xmin = xy.x;
                if(xy.x > xmax)
                   xmax = xy.x;
                if(xy.y < ymin)
                    ymin = xy.y;
                if(xy.y > ymax)
                    ymax = xy.y;
            }
        }
        else
        {
            // increase counter
            counter++;
        }
    }
    // set min and max values for x and y
    graph->setXMax(xmax);
    graph->setXMin(xmin);
    graph->setYMax(ymax);
    graph->setYMin(ymin);
    // return graph object
    return graph;
}
// process string to get the x and y points
void FileParser::processString(std::string& file, Axis& ax)
{
    // if string has data (assuming axis)
    if (!file.empty())
    {
        // parse string enough to be able to
        partialParse(file);
        // use a stream to gt values
        std::istringstream ss{file};
        // right here
        ss >> ax.x >> ax.y;
    }
    else
    {
        // error message
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Can't process string, empty line in file");
        messageBox.setFixedSize(500,200);
    }
}
// parse file enough to us stream to get x and y axis
void FileParser::partialParse(std::string& str)
{
    // get iterator to stop at first [
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    // remove everything between start and that [ iterator
    // so this removes the first - and not the - used to prepresent
    // negative numbers
    std::remove(std::begin(str), i, '-');
    // after first -, remove any char that matches condition below
    std::remove_if(std::begin(str), std::end(str), [](char c)
                                                    {
                                                        return c == ',' || c == '[' || c == ']';
                                                    });
}


