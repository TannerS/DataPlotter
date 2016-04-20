#include "fileparser.h"
#include <fstream>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "axis.h"
#include "boost/range/algorithm/find.hpp"
#include "boost/range/algorithm/remove_if.hpp"
#include <sstream>
#include <iostream>
#include <QVector>
#include "graph.h"
#include <limits>

Graph FileParser::processFile(boost::filesystem::path path)
{
    // create stream to open file
    boost::filesystem::fstream in;
    // open file using path
    in.open(path, std::ios::in);
    // temp Axis to pass between methods and set in graph object
    Axis xy;
    // temp graph
    Graph graph;
    // make copy of path
    boost::filesystem::path temp_path(path);
    // get rid of extension, this will be added later when producing image
    temp_path.replace_extension("");
    // set filename
    graph.setFileName(QString::fromStdString(temp_path.string()));
    std::cout << "DEBUG NAME: " << temp_path << std::endl;
    if (in.fail())
    {/* handle */}
    // used to skip the 14 lines of no data (needs to be dynamic later on)
    int counter = 0;//14
    // used to get x,y min,max
    float xmin = 0;
    float ymin = 0;
    float xmax = 0;
    float ymax = 0;
    // temp string to hold file
    std::string temp;
    // prase each file line
    while (getline(in, temp))
    {
        // if we are reading the data aprt of the file
        if(counter > 14)
        {
            // used to find min/max of each axis
            // process string to get xy axis
            processString(temp, xy);
            // get x coordinates, and no
            graph.getXAxisVector().push_back(xy.x);
            graph.getYAxisVector().push_back(xy.y);
            // first real line of data
            if(counter == 15)
            {
                // set up default min and max as the firts value
                xmin = xmax = xy.x;
                ymin = ymax = xy.y;
                counter++;
            }
            else
            {
                //compare to find min
                if(xy.x < xmin)
                    xmin = xy.x;
                if(xy.x > xmax)
                   xmax = xy.x;
                if(xy.y < ymin)
                    ymin = xy.y;
                if(xy.y > ymax)
                    ymax = xy.y;
                counter++;
            }
        }
        else
            counter++;
    }

    graph.setXMax(xmax);
    graph.setXMin(xmin);
    graph.setYMax(ymax);
    graph.setYMin(ymin);

   return graph;
}

void FileParser::processString(std::string& file, Axis& ax)
{
    if (!file.empty())
    {
        partialParse(file);
        std::istringstream ss{file};
        ss >> ax.x >> ax.y;
    }
}

void FileParser::partialParse(std::string& str)
{
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    std::remove(std::begin(str), i, '-');
    std::remove_if(std::begin(str), std::end(str), [](char c)
                                                    {
                                                        return c == ',' || c == '[' || c == ']';
                                                    });
}


