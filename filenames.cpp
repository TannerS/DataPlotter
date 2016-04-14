#include "filenames.h"
#include <string>
#include "boost/tokenizer.hpp"
#include <iostream>
#include <fstream>
#include "boost/regex.hpp"

FileNames::FileNames() : settings_name("file_names.csv")
{
}

FileNames::~FileNames()
{

}

void FileNames::getFileNames()
{
    // http://regexr.com/
    // (Test)(\s)*[0-9]*(\s)*?[=](\s)*?\w*(.txt);

    boost::regex expression("(Test)[0-9]*(\\s)*?[=](\\s)*?(\\w)*(.txt)");

    std::fstream input_file;

    input_file.open("file_names.csv", std::ios::in);

    if(input_file.fail())
    {
        // *********************************************do error connection
        std::cout << " error" << std::endl;
    }
    else
    {

    std::string temp = "";
    std::string line = "";
    std::string msg = "";

    std::cout << "HELLO: " << std::endl;

    while(std::getline(input_file, temp))
    {
            std::cout << "HELLO22: " << temp << std::endl;

        //boost::cmatch results;
        boost::match_results<std::string::const_iterator> results;

        //if(boost::regex_match(line, results, expression))
        if(boost::regex_match(temp, results, expression))
        {



            //if(msg)
               //msg.assign(results[0].first);
            std::cout << "TEST: " << msg << " : " << results[2] << std::endl;

            msg.clear();
        }

        /*
        int process_ftp(const char* response, std::string* msg)
        {
           cmatch what;
           if(regex_match(response, what, expression))
           {
              // what[0] contains the whole string
              // what[1] contains the response code
              // what[2] contains the separator character
              // what[3] contains the text message.
              if(msg)
                 msg->assign(what[3].first, what[3].second);
              return std::atoi(what[1].first);
           }
           // failure did not match
           if(msg)
              msg->erase();
              */


    }

/*
        // tokenize each line to get the info from
        boost::tokenizer<boost::escaped_list_separator<char>> tokenizer(input_file);

        for (boost::tokenizer<boost::escaped_list_separator<char>>::iterator iter(tokenizer.begin()); iter != tokenizer.end(); iter++)
        {
           this->names.push_back(*iter);
        }
        */
    }
}
