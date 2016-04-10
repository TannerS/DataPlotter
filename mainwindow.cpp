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
#include "boost/lexical_cast.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <ctime>
#include "filedata.h"

// http://www.boost.org/doc/libs/1_41_0/libs/filesystem/example/simple_ls.cpp

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGuiApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    ui->current_dir->setText(QDir::currentPath());
    data = new FileData();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete data;
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
        //allocate list of selected files (QStringList)
        initFiles(dialog.selectedFiles());
}


void MainWindow::initFiles(QStringList files)
{

    // temp path to use to hold information for file class
    // create path (init path, current dir??)
    boost::filesystem::path temp_path(boost::filesystem::initial_path());
    // get modified date of files
    time_t time;
    // loop all files
    for(int i = 0; i < files.size(); i++)
    {
        File path;
        // get complete path (new path object (path as string, native format))
        temp_path = boost::filesystem::system_complete(boost::filesystem::path((std::string)(files.at(i).toLocal8Bit().constData()), boost::filesystem::native));
        // check if path/file still exist
        if(!boost::filesystem::exists(temp_path))
        {
            QMessageBox messageBox;
            messageBox.critical(0,"Error","A file does not exist");
            messageBox.setFixedSize(500,200);
            break;
        }
        // does this get overwirtten each time???
        path.setPath(temp_path);
        // set the last modified time
        path.setModifiedTime(boost::filesystem::last_write_time(temp_path));

        data->addPath(path);
    }

   // vector<File>*


    for(int i = 0; i < files.size(); i++)
    {
        auto t = (data->getPaths());

        t->at(i);
        std::cout << "PATH: " << t->at(i).getPath() << std::endl;
        std::cout << "TIME: " << t->at(i).getModifiedTime() << std::endl;

    }



}


