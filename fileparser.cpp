#include "fileparser.h"
#include <fstream>
#include "boost/filesystem/path.hpp"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include "axis.h"
#include "boost/range/algorithm/find.hpp"
#include "boost/range/algorithm/remove_if.hpp"

FileParser::FileParser()
{

}

std::vector<Axis> FileParser::processFile(boost::filesystem::path path)
{
    //std::fstream in;
    boost::filesystem::fstream in;
    std::vector<Axis> vec;
    in.open(path, std::ios::in);

    std::string temp;

    if (in.fail())
    {
        // handle

    }

    while (getline(in, temp))
    {
        Point ax;
        processString(temp, ax);
        vec.push_back(ax);

        //000cout << p.x << " " << p.y << std::endl;
    }
    return vec;
}

//////////////////////////////////////////////////////////////////////////////////////////////////**********88
Axis FileParser::processString(std::string& file, Axis& ax)
{
    if (!file.empty())
    {
        partialParse(file, ax);
        std::istringstream ss{file};
        ss >> ax.x >> ax.y;
    }

    return cor;
}


std::string FileParser::partialParse(std::string& file)
{
    /*
    auto i{ std::find(std::begin(str), std::end(str), '[') };
    std::remove(std::begin(str), std::end(str), '-');
    std::remove_if(std::begin(str), std::end(str), [](char c)
                                                    {
                                                        return c == ',' || c == '[' || c == ']';
                                                    });
    */

    auto i { boost::range::find(boost::begin(str), std::end(str), '[')};
    boost::filesystem::remove(boost::begin(str), std::end(str), '-');
    boost::range::remove_if(boost::begin(str), std::end(str), [](char c)
                                                                {
                                                                    return c == ',' || c == '[' || c == ']';
                                                                });
}
