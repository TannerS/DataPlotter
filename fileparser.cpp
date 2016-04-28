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
#include "file.h"

void FileParser::processFiles()
{   
    for(int i = 0; i < paths.size(); i++)
    {
        // temp path with removed ext
        boost::filesystem::path temp_path(paths.at(i));
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
            // if we are reading the data aprt of the file
            if(counter > 14)
            {
                // process string to get xy axis
                processString(temp, xy);
                // get x,y coordinates
                graph.setXAxisVectorPoint(xy.x);
                graph.setYAxisVectorPoint(xy.y);
                // first real line of data
                if(counter == 15)
                {
                    // set up default min and max as the firts value
                    xmin = xmax = xy.x;
                    ymin = ymax = xy.y;
                    // one more so it does not enter this if statement agian
                    //****************************************************************use bool
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
                counter++;

            }
        }

        graph.setXMax(xmax);
        graph.setXMin(xmin);
        graph.setYMax(ymax);
        graph.setYMin(ymin);

        this->graphs.push_back(graph);
    }
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
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    std::remove(std::begin(str), i, '-');
    std::remove_if(std::begin(str), std::end(str), [](char c) { return c == ',' || c == '[' || c == ']'; });
}

void FileParser::storePaths(std::vector<File> new_paths)
        //QVector<boost::filesystem::path> new_paths)
{
    QVector<boost::filesystem::path> temp;

    for(int i = 0; i < new_paths.size(); i++)
        temp.push_back(new_paths.at(i).path);

    this->paths = temp;
}

void FileParser::stop()
{

}

void FileParser::run()
{
    FileParser::processFiles();
}

QVector<Graph> FileParser::getGraphs()
{
    return this->graphs;
}

