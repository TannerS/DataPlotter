#include "filenames.h"
#include <string>
#include "boost/tokenizer.hpp"
#include <iostream>
#include <fstream>
#include "boost/regex.hpp"
#include <QMessageBox>
#include <unordered_map>

FileNames::FileNames() : settings_name("file_names.csv")
{
}

 void FileNames::loadSettings()
{
    // http://regexr.com/
    // regular expression to follow format such that "Text <num> = <filename with num> (optional: _ <char><letters>).txt
    boost::regex expression("(\\s*)(Test)(\\s*)[0-9]*(\\s*)(=)(\\s*)[a-zA-Z]*[0-9]*((_)[a-zA-Z]*)?(.txt)(\\s*)");
    // instream to get file contents
    std::fstream input_file;
    // open up file
    input_file.open("file_names.csv", std::ios::in);
    // if error with file
    if(input_file.fail())
    {
        // error message
        QMessageBox messageBox;
        messageBox.critical(0,"Error","File: file_names.csv missing");
        messageBox.setFixedSize(500,200);
    }
    else
    {
        // string to get line from file
        std::string temp = "";
        // loop file getting each line
        while(std::getline(input_file, temp))
        {
            // hold string match results
            boost::match_results<std::string::const_iterator> results;
            // get results based off regualr expression
            if(boost::regex_match(temp, results, expression))
            {
                // set to use string methods
                temp = results[0];
                // remove all white spaces from text
                temp.erase(std::remove_if(temp.begin(), temp.end(), [](char pos){return std::isspace(pos);}), temp.end());
                // seperate string into two substrings, test and filename for test
                boost::regex filename_re("=");
                boost::sregex_token_iterator iter(temp.begin(), temp.end(), filename_re, -1);

                std::string x = (*iter);
                iter++;
                std::string y = (*iter);

                std::cout << "KEY: " << x << " VALUE: " << y << std::endl;

                std::pair<std::string, std::string> file_info (x,y);

                this->names.insert(file_info);

            }
        }
    }
}

 std::string FileNames::getMapValue(std::string str)
 {
     std::string temp;
    temp = this->names[str];
     return temp;
 }
