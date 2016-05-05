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
    std::cout << "DEBUG 8" << std::endl;
    // temp path with removed ext
    boost::filesystem::path temp_path(path);
    //************************************************************does this change original?
  //  std::cout << "DEBUG_: "<< temp_path.filename() << std::endl;

    //std::cout << "DEBUG_: "<< temp_path.parent_path() << std::endl;
    //std::cout << "DEBUG_: "<< temp_path.branch_path() << std::endl;
    //std::cout << "DEBUG_: "<< temp_path.generic_string() << std::endl;
    //std::cout << "DEBUG_: "<<  temp_path.relative_path()<< std::endl;
    //std::cout << "DEBUG_: "<< temp_path.root_directory() << std::endl;
    //std::cout << "DEBUG_: "<< temp_path.root_path()<< std::endl;
    //std::cout << "DEBUG_: "<<  temp_path.path() << std::endl;

    // create stream to open file
    boost::filesystem::fstream in;
    // open file using path
    //**************************************************************************8
    in.open(temp_path, std::ios::in);
    // remove ext so later we can use filename for photo name without the .xxx
    temp_path.replace_extension(".png");
    // temp Axis to pass between methods and set in graph object
    Axis xy;
    // temp graph
    Graph graph;
    // set filename
    graph.setFileName(QString::fromStdString(temp_path.string()));

    if (in.fail())
    {/* handle */}
    // used to skip the 14 lines of no data
    int counter = 0;
    // used to get x,y min,max
    float xmin = 0;
    float ymin = 0;
    float xmax = 0;
    float ymax = 0;
    // temp string to hold file
    std::string temp = "";
    // prase each file line
    while (getline(in, temp))
    {
        std::cout << "DEBUG 9" << std::endl;
        // if we are reading the data aprt of the file
        if(counter > 14)
        {
            std::cout << "DEBUG 10" << std::endl;
            // process string to get xy axis
            processString(temp, xy);
            // get x,y coordinates
            graph.setXAxisVectorPoint(xy.x);
            graph.setYAxisVectorPoint(xy.y);
            // first real line of data
            if(counter == 15)
            {
                std::cout << "DEBUG 11" << std::endl;
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
                std::cout << "DEBUG 12" << std::endl;
            }
        }
        else
        {
            counter++;
            std::cout << "DEBUG 13" << std::endl;
        }
    }

    graph.setXMax(xmax);
    graph.setXMin(xmin);
    graph.setYMax(ymax);
    graph.setYMin(ymin);
std::cout << "DEBUG 14" << std::endl;
    return graph;
}

void FileParser::processString(std::string& file, Axis& ax)
{
     std::cout << "DEBUG 15" << std::endl;
    if (!file.empty())
    {
         std::cout << "DEBUG 16" << std::endl;
        partialParse(file);
        std::istringstream ss{file};
 std::cout << "DEBUG 17" << std::endl;
        ss >> ax.x >> ax.y;
         std::cout << "DEBUG 18" << std::endl;
    }
}

void FileParser::partialParse(std::string& str)
{
     std::cout << "DEBUG 19" << std::endl;
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    std::remove(std::begin(str), i, '-');
    std::remove_if(std::begin(str), std::end(str), [](char c)
                                                    {
                                                        return c == ',' || c == '[' || c == ']';
                                                    });
}


