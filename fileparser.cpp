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

void FileParser::processFile(boost::filesystem::path path)
{
    //std::fstream in;
    boost::filesystem::fstream in;
    //std::vector<Axis> vec;
    in.open(path, std::ios::in);

    std::cout << "DEBUG: " << std::endl;

    std::string temp;

    if (in.fail())
    {
        // handle

    }

    while (getline(in, temp))
    {
        Axis ax;
        std::cout << "DEBUG STRING : "<< temp << std::endl;
        this->processString(temp, ax);
        //vec.push_back(ax);
        this->points.push_back(ax);
    }
   // return vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////**********88
void FileParser::processString(std::string& file, Axis& ax)
{
    if (!file.empty())
    {
        partialParse(file);
        std::istringstream ss{file};
            std::cout << "DEBUG SSTREAM STEP: "<< file << std::endl;
        ss >> ax.x >> ax.y;
        std::cout << "DEBUG x && Y: "<< ax.x << " " << ax.y<< std::endl;
    }
}


void FileParser::partialParse(std::string& str)
{

    std::cout << "DEBUG PARSE PART 1 : "<< str << std::endl;
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    std::remove(std::begin(str), i, '-');

        std::cout << "DEBUG PARSE PART 2 : "<< str << std::endl;

    std::remove_if(std::begin(str), std::end(str), [](char c)
                                                    {
                                                        return c == ',' || c == '[' || c == ']';
                                                    });

        std::cout << "DEBUG PARSE PART 3 : "<< str << std::endl;
}



std::vector<Axis> FileParser::getPoints()
{
    return this->points;
}
