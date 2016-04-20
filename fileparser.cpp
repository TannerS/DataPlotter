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

QVector<double> FileParser::processFile(boost::filesystem::path path)
{
    //std::fstream in;
    boost::filesystem::fstream in;
    QVector<Axis> vec;
    in.open(path, std::ios::in);
    std::string temp;

    if (in.fail())
    {
        // handle

    }

    while (getline(in, temp))
    {
        Axis ax;
        std::cout << "DEBUG STRING : "<< temp << std::endl;
        processString(temp, ax);
        vec.push_back(ax);
    }

   return vec;
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


