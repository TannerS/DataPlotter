#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QStringList>
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"
#include "boost/lexical_cast.hpp"
#include "grapher.h"

// constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // set up UI
    ui->setupUi(this);
    // may remove
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    // init data that is a filedata object and contains vector of files that contain info on the files
    this->data = new FileData();
    // create object to load file names
    this->names = new FileNames();
    // create object to parse file
    this->parser = new FileParser();
    // create object to process graphs
    this->grapher = new Grapher();
}
// destructor
MainWindow::~MainWindow()
{
    // free up memory
    delete this->ui;
    delete this->data;
    delete this->names;
    delete this->parser;
    delete this->grapher;
}
// when user clicks a button to rename files
// name was let over from previous version
// this is why name does not match
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
    // error
    else
    {
        // display message
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Problem opening file(s)");
        messageBox.setFixedSize(500,200);
    }
}
// get files ready
void MainWindow::initFiles(QStringList files)
{
    // if paths have been calculated do a prior method, reset
    // this fixes a problem I had
    if(data->getPaths().size() != 0)
        // reset paths
        data->pathReset();
    // create temp path
    boost::filesystem::path temp_path(boost::filesystem::initial_path());
    // create temp File object
    File path;
    // loop all files
    for(int i = 0; i < files.size(); i++)
    {
        // get complete path (new path object (path as string, native format))
        // this will get the file from the dir (path + filename + ext)
        temp_path = boost::filesystem::system_complete(boost::filesystem::path((std::string)(files.at(i).toLocal8Bit().constData()), boost::filesystem::native));
        // check if path/file still exist
        if(!boost::filesystem::exists(temp_path))
        {
            // display error
            QMessageBox messageBox;
            messageBox.critical(0,"Error","A file does not exist");
            messageBox.setFixedSize(500,200);
            break;
        }
        else
        {
            // set the path to the
            path.path = temp_path;
            // set the last modified time of the file
            path.last_modified_state = boost::filesystem::last_write_time(temp_path);
            // add path to list of paths
            data->addPath(path);
        }
    }
}
// function to rename files
void MainWindow::renameFiles()
{
    // tep vector to maintain paths
    // this eventually will be set into object
    // to use later
    std::vector<File> new_paths;
    // temp file object
    File temp_file;
    // set up file names
    this->names->loadSettings();
    // sort paths by modified time
    // this is needed for later
    this->data->sortByTime();
    // get paths of selected files
    std::vector<File> files = (data->getPaths());
    // loop all selected files
    for(int i = 0; i < files.size(); i++)
    {
        // the csv file is in terms of Test 1 = filename.text
        // since systems paths are sorted by modified date, we can use the fact that it is in order
        // to create a new file name such that Test 1,2,3,4.. etc and use the hashmap
        // to get the file name from that string (Test 1....)
        // create name
        std::string file_name = ("Test" + boost::lexical_cast<std::string>(i + 1));
        // get mapping to proper filename from hashmap
        file_name = this->names->getMapValue(file_name);
        // *******************************************
        // since we are appending \\, this only works for windows not for Linux/mac
        // create new path where we get full path into constructor
        boost::filesystem::path temp(std::string(files.at(i).path.parent_path().string() + "\\" + file_name));
        // if path exist
        if ( boost::filesystem::exists( files.at(i).path ) )
        {
            try
            {
                // attemp to rename current file with file name off .csv file
                boost::filesystem::rename( files.at(i).path, temp );
                // get info of file
                temp_file.last_modified_state = files.at(i).last_modified_state;
                temp_file.path = temp;
                // push it into vector
                new_paths.push_back(temp_file);
            }
            // if error occurs for any reason
            catch (const boost::filesystem::filesystem_error& e)
            {
                // error message
                QMessageBox messageBox;
                messageBox.critical(0,"Error", "Problem renaming file(s)");
                messageBox.setFixedSize(500,200);
            }
        }
        // if path doesn't exist
        else
        {
            // error message
            QMessageBox messageBox;
            //messageBox.critical(0,"Error: a file is unable to be renamed");
            messageBox.setFixedSize(500,200);
        }
    }
    // put paths into class object
    this->data->setPaths(new_paths);
    // sort them by time
    // this is for a fix
    // of the order
    this->data->sortByTime();
}
// function to parse and graph the plots
void MainWindow::ParseFiles()
{
    // reset graphs
    // this fixed problem with graphs
    // over lapping on each other
    // from a previous run
    if(this->grapher->getGraphs().size() != 0)
        this->grapher->graphReset();
    // loop files selected earlier
    for(int i = 0; i < this->data->getPaths().size(); i++)
    {
        // get path at pos i
        // process that path to return a graph
        // graph is added to a vector to be graphed later
        this->grapher->addGraph(this->parser->processFile(this->data->getPaths().at(i).path));
        // generate graph and save image at graph i
        this->grapher->generateGraph(i);
    }
    // delete graphs
    this->grapher->deleteGraphs();
}
// when click button to plot
void MainWindow::on_plot_files_clicked()
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
        // allocate list of selected files
        initFiles(dialog.selectedFiles());
        // parse the files passed in from UI
        this->ParseFiles();
    }
    // error
    else
    {
        // display message
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Problem opening file(s)");
        messageBox.setFixedSize(500,200);
    }
}
