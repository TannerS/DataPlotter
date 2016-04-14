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
#include <qcustomplot.h>
    //todo
/*
 *  pattern matching**
 *  file stuff
 *  renaming files
 *  UI
 *  should work for multi platform ****
 *  Plotting and save image for plotting *******
 *  parsing file for x,y *****
 * sorting by function poiter and boost*&***
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
    this->names = new FileNames();
}

MainWindow::~MainWindow()
{
    // free up memory
    delete ui;
    delete data;
    delete this->names;
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
        //***************************************************************************more mem effeicnt way of doing this?
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
        path.setPath(temp_path);
        // set the last modified time
        path.setModifiedTime(boost::filesystem::last_write_time(temp_path));
        // add path to list
        data->addPath(path);
    }
}

void MainWindow::renameFiles()
{
    // get the file names
    this->names->getFileNames();

    /*
    boost::filesystem::path pa("C://users/Tanner Summers/file.txt");

    std::cout <<pa.filename() << std::endl;
    // folder it is in **
    std::cout <<pa.branch_path() << std::endl;
    // file name??
    std::cout <<pa.leaf() << std::endl;
    // folder it is in??
    std::cout <<pa.parent_path() << std::endl;
    // path + filename
    std::cout <<pa.relative_path() << std::endl;
    /// end debug
    */

    /*
    for(int i = 0; i < size; i++)
    {
        auto t = (data->getPaths());
        // what happens to old reference to the path? should i put that into list instead?*********************************
        //**********************************************************************************neeed to check for which OS, unix uses / not \
        boost::filesystem::path temp(std::string(t->at(i).getPath().parent_path().string() + "\\" + str[i]));

        std::cout << "PATH!!!: " << temp << std::endl;

        if ( boost::filesystem::exists( temp ) )
        {
            try
            {
                boost::filesystem::rename( t->at(i).getPath(), temp );
            }
            catch (const boost::filesystem::filesystem_error& e)
            {
                std::cout << "ERROR: " << e.code()<< std::endl;
            }
        }

        //std::cout << "PATH: " << t->at(i).getPath() << std::endl;
        //std::cout << "PATH: " << t->at(i). << std::endl;
        //std::cout << "TIME: " << t->at(i).getModifiedTime() << std::endl;

    }
*/

}

void MainWindow::test()
{



    /*
     *
     * struct student
{
  string name;
  string grade;
};

bool cmd(const student & s1, const student & s2)
{
   if (s1.name != s2.name) return s1.name < s2.name;
   return s1.grade < s2.grade;
}


vector<student> s;
sort(s.begin(), s.end(), cmd);
     *
     * /



    /*
    // file name**
    std::cout <<temp_path.filename() << std::endl;
    // folder it is in **
    std::cout <<temp_path.branch_path() << std::endl;
    // file name??
    std::cout <<temp_path.leaf() << std::endl;
    // folder it is in??
    std::cout <<temp_path.parent_path() << std::endl;
    // path + filename
    std::cout <<temp_path.relative_path() << std::endl;



    //QCustomPlot plotter;

    //customPlot is a pointer to the QCustomPlot


    //plotter->addGraph();
   // plotter->graph(0)->setPen(QPen(Qt::blue));



    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph
    customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::red)); // line color red for second graph
    // generate some points of data (y0 for first, y1 for second graph):
    QVector<double> x(250), y0(250), y1(250);
    for (int i=0; i<250; ++i)
    {
      x[i] = i;
      y0[i] = qExp(-i/150.0)*qCos(i/10.0); // exponentially decaying cosine
      y1[i] = qExp(-i/150.0);              // exponential envelope
    }
    // configure right and top axis to show ticks but no labels:
    // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    // make left and bottom axes always transfer their ranges to right and top axes:
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    // pass data points to graphs:
    customPlot->graph(0)->setData(x, y0);
    customPlot->graph(1)->setData(x, y1);
    // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
    customPlot->graph(0)->rescaleAxes();
    // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
    customPlot->graph(1)->rescaleAxes(true);
    // Note: we could have also just called customPlot->rescaleAxes(); instead
    // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    */
}
