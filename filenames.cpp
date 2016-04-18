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
    // creat map of test to filename for said test
    //names = new std::unordered_map<std::string, std::string>();
}

FileNames::~FileNames()
{
    // free memory
    //delete this->names;
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

/*
                std::unordered_map<std::string,std::string>::const_iterator iter2 = names.find (x);

                 if (iter2 == names.end())
                 {
                             std::cout << " ************************************************************************** " ;
                   //1return iter2->second;
                 }
                 else
                   std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " ;


                // http://stackoverflow.com/questions/9926544/assigning-value-into-unordered-map-pointer-after-creating-a-instance-of-it
*/
            }
        }
    }
}

 std::string FileNames::getMapValue(std::string str)
 {
     // http://stackoverflow.com/questions/9926544/assigning-value-into-unordered-map-pointer-after-creating-a-instance-of-it

     std::string temp;

    // (*this->Accounts)["hello"] = "test";
     //cout << (*this->Accounts)["hello"];
    temp = this->names[str];
    // std::cout << "DEBUG : " << ((this->names)[str]) << " END DEBUG" << std:: endl;
     return temp;

/*
     std::unordered_map<std::string,std::string>::const_iterator iter = names.find ("Test 2");

      if (iter == names.end())
      {
                  std::cout << " ************************************************************************** " ;
        return iter->second;
      }
      else
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " ;

      std::cout << std::endl;
      */
     //return nullptr;
 }
