#include "filenames.h"
#include "boost/tokenizer.hpp"
#include <fstream>
#include "boost/regex.hpp"
#include <QMessageBox>
#include <unordered_map>

// set file name this way set it is const var
FileNames::FileNames() : settings_name("file_names.csv")
{/*empty body*/}
// load settings from .cvs file, basically, this is the file names
void FileNames::loadSettings()
{
    // regular expression to follow format such that "Text <num> = <filename with num> (optional: _ <char><letters>).txt
    // this is best practice to be sure the file is not having to be exaclty type in as some way
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
    // file is fine
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
                // anything after results[0]is for other purposes
                temp = results[0];
                // remove all white spaces from text
                temp.erase(std::remove_if(temp.begin(), temp.end(), [](char pos){return std::isspace(pos);}), temp.end());
                // seperate string into two substrings, test and filename for test
                // based off = sign
                boost::regex filename_re("=");
                // iterator object based off start of vector, end of vector, and the =
                // can't recall what the -1 was for
                boost::sregex_token_iterator iter(temp.begin(), temp.end(), filename_re, -1);
                // since the strings are now seperated as tokens
                // this returns the test number e.g. test=1,2,3,...etc
                std::string test_number = (*iter);
                // get next address (next test value)
                iter++;
                // get test name e.g. HapticTask1_Fatigue.txt, etc
                std::string test_name = (*iter);
                // no need to iterate here
                // pass in the test value and name into a pair
                // this will be used for later
                // to get values off hashmap to match file name with
                // proper file that was loaded into program
                std::pair<std::string, std::string> file_info (test_number, test_name);
                // insert new pair (into hashmap)
                this->names.insert(file_info);
            }
        }
    }
}
// get value from map based off test value
std::string FileNames::getMapValue(std::string str)
{
    // this is how you access it in C++, well one way
    return this->names[str];
}
