#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>
#include <QDebug>
#include <QMessageBox>
#include <QStringList>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/filesystem.hpp"
#include "boost/filesystem/fstream.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <ctime>
#include <qcustomplot.h>
#include <algorithm>
#include <fstream>

#include <boost/spirit/include/qi.hpp>
        #include <string>
        #include <iostream>

    //todo
/*
 * if file already exist when renaming***********
 *  file stuff
 *  renaming files
 *  Plotting and save image for plotting *******
 *  parsing file for x,y *****

 *
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set up UI
    ui->setupUi(this);
    // may remove
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // set default UI's element path as current path
    ui->current_dir->setText(QDir::currentPath());
    // init data that is a filedata object and contains vector of files that contain info on the files
    this->data = new FileData();
    // create object to load file names
    this->names = new FileNames();
    // create object to parse file
    this->parser = new FileParser();
}

MainWindow::~MainWindow()
{
    // free up memory
    delete ui;
    delete data;
    delete names;
    delete this->parser;
}

void MainWindow::on_select_dir_clicked()
{
    // this = parent pointer, rest has default values
    QFileDialog dialog(this);
    // set encoding and type of files to accept
    dialog.setNameFilter(trUtf8("txt (*.txt)"));
    // allow user to select multiple files
    dialog.setFileMode(QFileDialog::ExistingFiles);
    // needed to make it open properly
    if (dialog.exec())
    {
        // allocate list of selected files (QStringList)
        initFiles(dialog.selectedFiles());
        // rename files
        renameFiles();
    }
}

void MainWindow::initFiles(QStringList files)
{
    // create path (init path, current dir??)
    boost::filesystem::path temp_path(boost::filesystem::initial_path());
    // loop all files
    for(int i = 0; i < files.size(); i++)
    {
        // temp file object
        File path;
        // get complete path (new path object (path as string, native format))
        temp_path = boost::filesystem::system_complete(boost::filesystem::path((std::string)(files.at(i).toLocal8Bit().constData()), boost::filesystem::native));
        // check if path/file still exist**********************************************needs testing
        if(!boost::filesystem::exists(temp_path))
        {
            // problem
            //  **********************************************needs testing
            QMessageBox messageBox;
            messageBox.critical(0,"Error","A file does not exist");
            messageBox.setFixedSize(500,200);
            break;
        }
        // set the path to the
        //path.setPath(temp_path);
        path.path = temp_path;
        // set the last modified time
        //path.setModifiedTime(boost::filesystem::last_write_time(temp_path));
        path.last_modified_state = boost::filesystem::last_write_time(temp_path);
        // add path to list
        data->addPath(path);
    }
}

void MainWindow::renameFiles()
{

    std::vector<File> new_paths;
    //File* temp_file;
    File temp_file;

    // set up file names
    this->names->loadSettings();
    // sort paths by modified time
    this->data->sortByTime();
    // get paths of selected files
    auto t = (data->getPaths());
    // loop all selected files
    for(int i = 0; i < t.size(); i++)
    {
        // the csv file is in terms of Test 1 = filename.text
        // since systems paths are sorted by modified date, we can use the fact that it is in order
        // to create a new file name such that Test 1,2,3,4.. etc and use the hashmap
        // to get the file name from that string (Test 1....)
        // create name
        std::string file_name = ("Test" + boost::lexical_cast<std::string>(i + 1));
        // get mapping to proper filename from hashmap

        file_name = this->names->getMapValue(file_name);

      //  std::cout << "FILE--------->: " << this->names->getMapValue(file_name) << std::endl;

        // what happens to old reference to the path? should i put that into list instead?*********************************
        //**********************************************************************************neeed to check for which OS, unix uses / not \

        boost::filesystem::path temp(std::string(t.at(i).path.parent_path().string() + "\\" + file_name));

       // std::cout << "PATH : " << t.at(i).path << std::endl;
        //std::cout << "PATH-: " << temp << std::endl;
        // if path exist (needs testng!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!)
        if ( boost::filesystem::exists( t.at(i).path ) )
        {
            try
            {
               // std::cout << "ENTER HERE " << temp << std::endl;
                // rename file from .getPath to temp
                //////////////////////////////////////////////////*******************************************************************************uncomment
                boost::filesystem::rename( t.at(i).path, temp );
                // http://stackoverflow.com/questions/39912/how-do-i-remove-an-item-from-a-stl-vector-with-a-certain-value

                // get info before rename and make new vecto with same info except new renamed paths
                //temp_file = new File();
                temp_file.last_modified_state = t.at(i).last_modified_state;
                temp_file.path = temp;
                //t.erase(std::remove(t.begin(), t.end(), i), t.end());
                new_paths.push_back(temp_file);
                //delete temp_file;

            }
            catch (const boost::filesystem::filesystem_error& e)
            {
                // error message
                QMessageBox messageBox;
                //messageBox.critical(0,"Error: a file is unable to be renamed");
                messageBox.setFixedSize(500,200);
            }
        }
        else
        {
            // error message
            QMessageBox messageBox;
            //messageBox.critical(0,"Error: a file is unable to be renamed");
            messageBox.setFixedSize(500,200);
        }

        //std::cout << "PATH: " << t.at(i).path << std::endl;
       // std::cout << "TIME: " << t.at(i).last_modified_state << std::endl;

    }

    this->data->setPaths(new_paths);
    this->data->sortByTime();
/*
    std::vector<File>::iterator i;

    for(i = this->data->getPaths().begin(); i != this->data->getPaths().end(); ++i)
    {
        std::cout << "DEBUG _____: " << (*i).path << std::endl;



    }
*/

    //ParseFiles();
}

void MainWindow::ParseFiles()
{
    //boost::filesystem::fstream input;

    std::fstream input;

    std::string s = this->data->getPaths().at(0).path.string();

std::cout << "FILE: " << s << '\n';

    input.open(s, std::ios::in);

    if(input.fail())
    {
        QMessageBox messageBox;
        //messageBox.critical(0,"Error: File: " <<  this->data->getPaths().at(0).path << " is missing");
        messageBox.setFixedSize(500,200);
        std::cout << "ERROR!!" << '\n';
    }
    else
    {
        std::cout << "here" << '\n';

        std::string str[] = {"- [-48.0093, 41.5957, -66.8010, 18202.0]",
                         "- [-48.0285, 41.6264, -66.7606, 18203.1]",
                         "- [-48.0061, 41.6415, -66.8078, 18204.0]"};

          std::getline(std::cin, s);


          auto it = s.begin();

          bool match = boost::spirit::qi::parse(it, s.end(), boost::spirit::ascii::digit);
          std::cout << std::boolalpha << match << '\n';
          if (it != s.end())
            std::cout << std::string{it, s.end()} << '\n';



          std::cout << "here2" << '\n';

    }



}
