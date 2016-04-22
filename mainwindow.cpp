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
#include "axis.h"

#include <boost/spirit/include/qi.hpp>
        #include <string>
        #include <iostream>
#include "grapher.h"

    //todo
/*
 * if file already exist when renaming***********
 *  error checking
 * deletes when needed
 * convert other stuff to deletes from statics\
eat up worthless liness



path, fileinfo etc for ploting
 *
 */

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set up UI
    ui->setupUi(this);
    // may remove
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // set default UI's element path as current path
    //ui->current_dir->setText(QDir::currentPath());
    // init data that is a filedata object and contains vector of files that contain info on the files
    this->data = new FileData();
    // create object to load file names
    this->names = new FileNames();
    // create object to parse file
    this->parser = new FileParser();
    // create object to process graphs
    this->grapher = new Grapher();
}

MainWindow::~MainWindow()
{
    // free up memory
    delete ui;
    delete data;
    delete names;
    delete this->parser;
    delete this->grapher;
}

void MainWindow::on_select_files_clicked()
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
    //if paths have been calculated do a prior method, reset
    if(data->getPaths().size() != 0)
    {
        data->pathReset();
        std::cout << "DEBUG 1" << std::endl;
    }
   // else
    //{
        std::cout << "DEBUG 2" << std::endl;
        // create path
        boost::filesystem::path temp_path(boost::filesystem::initial_path());
        // loop all files
        for(int i = 0; i < files.size(); i++)
        {
            std::cout << "DEBUG 3" << std::endl;
            // temp file object
            File path;
            // get complete path (new path object (path as string, native format))
            temp_path = boost::filesystem::system_complete(boost::filesystem::path((std::string)(files.at(i).toLocal8Bit().constData()), boost::filesystem::native));
            // check if path/file still exist**********************************************needs testing
            if(!boost::filesystem::exists(temp_path))
            {
                QMessageBox messageBox;
                messageBox.critical(0,"Error","A file does not exist");
                messageBox.setFixedSize(500,200);
                break;
            }
            else
            {
                // set the path to the
                //path.setPath(temp_path);
                path.path = temp_path;
                // set the last modified time
                //path.setModifiedTime(boost::filesystem::last_write_time(temp_path));
                path.last_modified_state = boost::filesystem::last_write_time(temp_path);
                // add path to list
                data->addPath(path);
                std::cout << "DEBUG 4" << std::endl;
            }
       // }
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
        // need to modified for unix
        boost::filesystem::path temp(std::string(t.at(i).path.parent_path().string() + "\\" + file_name));
        // if path exist
        if ( boost::filesystem::exists( t.at(i).path ) )
        {
            try
            {
                boost::filesystem::rename( t.at(i).path, temp );
                // get info before rename and make new vector with same info except new renamed paths
                temp_file.last_modified_state = t.at(i).last_modified_state;
                temp_file.path = temp;
                new_paths.push_back(temp_file);
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
    }

    this->data->setPaths(new_paths);
    this->data->sortByTime();
}

void MainWindow::ParseFiles()
{
    //reset graphs
    if(this->grapher->getGraphs()->size() != 0)
    {
        std::cout << "DEBUG 7.1" << std::endl;
        this->grapher->graphReset();
    }
  //  else
    //{
        std::cout << "DEBUG 8" << std::endl;
        // loop files selected earlier
        for(int i = 0; i < this->data->getPaths().size(); i++)
        {
            // process path and add graph object to grapher's built in
            // graph object array
            // this method also collects info from the file
            // then adds graph
            this->grapher->addGraph(this->parser->processFile(this->data->getPaths().at(i).path));
           // // generate graph and save image
            std::cout << "START!!!!!!!!!!!!! " << " " << this->data->getPaths().at(i).path << " "<< this->data->getPaths().size() << std::endl;
            this->grapher->generateGraph(i);
            std::cout << "ENDT!!!!!!!!!!!!! " << std::endl;
        }
    //}
}

void MainWindow::on_plot_files_clicked()
{
    std::cout << "DEBUG 5" << std::endl;
    // this = parent pointer, rest has default values
    QFileDialog dialog(this);
    // set encoding and type of files to accept
    dialog.setNameFilter(trUtf8("txt (*.txt)"));
    // allow user to select multiple files
    dialog.setFileMode(QFileDialog::ExistingFiles);
    // needed to make it open properly
    if (dialog.exec())
    {
        std::cout << "DEBUG 6" << std::endl;
        // allocate list of selected files (QStringList)
        initFiles(dialog.selectedFiles());
        // rename files
        ParseFiles();
        std::cout << "DEBUG 7" << std::endl;
    }

}
