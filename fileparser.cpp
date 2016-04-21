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
    // make copy of path
   // boost::filesystem::path temp_path(path);
    // get rid of extension, this will be added later when producing image
   // temp_path.replace_extension("");
    // set filename
    graph.setFileName(QString::fromStdString(temp_path.string()));
    //std::cout << "DEBUG NAME: " << temp_path<< std::endl;
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
    std::string temp = "";
    // prase each file line
    while (getline(in, temp))
    {
           // std::cout << "LINE: " << temp<< std::endl;


        // if we are reading the data aprt of the file
        if(counter > 14)
        {
            // used to find min/max of each axis
            // process string to get xy axis
            processString(temp, xy);
            // get x coordinates, and no
           // graph.getXAxisVector().push_back(xy.x);
            //graph.getYAxisVector().push_back(xy.y);

            graph.setXAxisVectorPoint(xy.x);
            graph.setYAxisVectorPoint(xy.y);




            for(int i = 0 ;i < 100; i++)
            {
               // std::cout <<"NEW: " << xy.x << " " << xy.y << std::endl;
            }


            for(int i = 0 ;i < 100; i++)
            {
               // std::cout <<"NEW: " << graph.getXAxisVector().at(i) << " " << graph.getYAxisVector().at(i) << std::endl;
            }







            // first real line of data
            if(counter == 15)
            {
                // set up default min and max as the firts value
                xmin = xmax = xy.x;
                ymin = ymax = xy.y;

                // set graph size plus offset
              //  float x_data_range_min = 0;
               // float y_data_range_min = 0;
              //  float x_data_range_max = 0;
              //  float y_data_range_max = 0;

              //  std::cout << "DEBUG RANGE: "<< std::endl;
              //  std::cout << "XMAX: "<<  xmax << std::endl;
              //  std::cout << "XMIN: "<< xmin<<  std::endl;
              //  std::cout << "YMAX: "<<  ymax  << std::endl;
              //  std::cout << "YMIN: "<< ymin<<  std::endl;

                // one more so it does not enter this if statement agian
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
               // counter++;
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
  //  std::cout << "DEBUG POINTS: " << ax.x <<  " " << ax.x<< std::endl;
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


