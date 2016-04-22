#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>

// set plotter to 0 aka null
Grapher::Grapher() : plotter(nullptr)
{
    plotter = new QCustomPlot;
    graphs = new QVector<Graph>();
}

Grapher::~Grapher()
{
    if (plotter)
      delete plotter;
    delete graphs;
    delete curve;
}

QVector<Graph>* Grapher::getGraphs()
{
    return this->graphs;
}

void Grapher::generateGraph(int i)
{
     std::cout << "DEBUG 15" << std::endl;
    //***********************************************use local curve, and erase info dont allocate one within class
    Graph temp(this->graphs->at(i));
    // add graph
    plotter->addGraph();
    // create curve since our data needs it to do what it needs to do and can
    // only do it while using a curve
    curve = new QCPCurve(plotter->xAxis, plotter->yAxis);
    // add curve lines to graph
    plotter->addPlottable(curve);
    // *************************************************************may not beed needed
    curve->setLineStyle((QCPCurve::LineStyle)QCPCurve::lsLine);
    // *************************************************************may not beed needed
    curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 1));
    curve->setData(temp.getXAxisVector(), temp.getYAxisVector());
    // set axis
    plotter->xAxis->setLabel("X");
    // sext axis
    plotter->yAxis->setLabel("Y");
    // set graph size plus offset
    float x_data_range_min = temp.getXMin();
    float y_data_range_min = temp.getYMin();
    float x_data_range_max = temp.getXMax();
    float y_data_range_max = temp.getYMax();
    // set ranges with offset
    plotter->xAxis->setRange(x_data_range_min-5, x_data_range_max+5);
    plotter->yAxis->setRange(y_data_range_min-5, y_data_range_max+5);
    // set it up
    plotter->replot();
    // save as image
    plotter->savePng(temp.getFileName());
    // close graph
    plotter->close();
    // clear data for next graph (if need be)
    curve->clearData();
     std::cout << "DEBUG 16" << std::endl;
}

bool Grapher::addGraph(Graph g)
{
     std::cout << "DEBUG 17" << std::endl;
    this->graphs->push_back(g);
    return true;
}

void Grapher::graphReset()
{
     std::cout << "DEBUG 18" << std::endl;
    this->graphs->clear();
}




/*
#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>

// set plotter to 0 aka null
//********************************************test nullptr
Grapher::Grapher() : plotter(0)
{
    plotter = new QCustomPlot;
    //plotter->savePng(qApp->applicationDirPath()+"/output.png", 500, 300);
    graphs = new QVector<Graph>();
}

Grapher::~Grapher()
{
    if (plotter)
      delete plotter;
    delete graphs;
}

QVector<Graph>* Grapher::getGraphs()
{
    return this->graphs;
}

void Grapher::generateGraph(int i)
{
    // http://www.qcustomplot.com/index.php/support/forum/201
    Graph temp(this->graphs->at(i));


        // add graph
        plotter->addGraph();
        //QCPCurve* curve = new QCPCurve(plotter->xAxis, plotter->yAxis);
        //plotter->addPlottable(curve);
        // fixes a lot
        plotter->graph(0)->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);

plotter->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 3));


    for(int i = 0 ;i < temp.getXAxisVector().size(); i++)
    {
        std::cout <<"(" << temp.getXAxisVector().at(i) << " " <<temp.getYAxisVector().at(i) <<")" << std::endl;
    }

    plotter->graph(0)->setData(temp.getXAxisVector(), temp.getYAxisVector());
    // set axis
    plotter->xAxis->setLabel("X");
    // sext axis
    plotter->yAxis->setLabel("Y");
    // set graph size plus offset
    float x_data_range_min = temp.getXMin();
    float y_data_range_min = temp.getYMin();
    float x_data_range_max = temp.getXMax();
    float y_data_range_max = temp.getYMax();

   // std::cout << "DEBUG RANGE: "<< std::endl;
  //  std::cout << "XMAX: "<<  x_data_range_max << std::endl;
  //  std::cout << "XMIN: "<< x_data_range_min<<  std::endl;
  // std::cout << "YMAX: "<<  y_data_range_max << std::endl;
  //  std::cout << "YMIN: "<< y_data_range_min<<  std::endl;



    plotter->xAxis->setRange(x_data_range_min-5, x_data_range_max+5);
    plotter->yAxis->setRange(y_data_range_min-5, y_data_range_max+5);

    // set it up
    plotter->replot();
    // save as image
    //QString str = this->graphs->at(i).
   //std::cout << "DEBUG NAME2: " << temp.getFileName()<< std::endl;

    plotter->savePng(temp.getFileName());
        plotter->saveJpg("test.jpg");
       // plotter->s
    // close graph
    plotter->close();
}

bool Grapher::addGraph(Graph g)
{
    this->graphs->push_back(g);
    return true;
}






/*
 *
 *
 * #include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>

// set plotter to 0 aka null
//********************************************test nullptr
Grapher::Grapher() : plotter(0)
{
    plotter = new QCustomPlot;
    //plotter->savePng(qApp->applicationDirPath()+"/output.png", 500, 300);
    graphs = new QVector<Graph>();
}

Grapher::~Grapher()
{
    if (plotter)
      delete plotter;
    delete graphs;
}

QVector<Graph>* Grapher::getGraphs()
{
    return this->graphs;
}

void Grapher::generateGraph(int i)
{
    // http://www.qcustomplot.com/index.php/support/forum/201
    //QString str = QString::fromStdString(name);
    //this->plotter = new QCustomPlot(plotter);
    //this->plotter = plotter;

// Graph temp = this->graphs->at(i);
    Graph temp(this->graphs->at(i));

    // add graph
    plotter->addGraph();

        plotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

       // plotter->graph(0)->setScatterStyle(QCPScatterStyle::ssDot );
        plotter->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 5));







    // set vector data
   // QVector<double> x(temp.getXAxisVector());
  //  QVector<double> x = temp.getXAxisVector();
    //QVector<double> y = temp.getYAxisVector();
    // add data to graph


   // std::cout << "DEBUG POINTS: "<< std::endl;

    for(int i = 0 ;i < 1; i++)
    {
        //std::cout <<x[i] << " " << y[i] << std::endl;
    }

    plotter->graph(0)->setData(temp.getXAxisVector(), temp.getYAxisVector());
    // set axis
    plotter->xAxis->setLabel("X");
    // sext axis
    plotter->yAxis->setLabel("Y");
    // set graph size plus offset
    float x_data_range_min = temp.getXMin();
    float y_data_range_min = temp.getYMin();
    float x_data_range_max = temp.getXMax();
    float y_data_range_max = temp.getYMax();

   // std::cout << "DEBUG RANGE: "<< std::endl;
  //  std::cout << "XMAX: "<<  x_data_range_max << std::endl;
  //  std::cout << "XMIN: "<< x_data_range_min<<  std::endl;
  // std::cout << "YMAX: "<<  y_data_range_max << std::endl;
  //  std::cout << "YMIN: "<< y_data_range_min<<  std::endl;



    plotter->xAxis->setRange(x_data_range_min-5, x_data_range_max+5);
    plotter->yAxis->setRange(y_data_range_min-5, y_data_range_max+5);



    // disable filling
     //plotter->legend->setBrush(QBrush(Qt::NoBrush));
     //plotter->s

    // plotter->graph(0)->setBrush(QBrush(Qt::NoBrush));
    // plotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 50)));

   //  customPlot->graph(0).se

             //setPen(QPen(Qt::red));
     //customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

            // customPlot->graph(0)
             //QCPGraph::setBrush(Qt::);

             //QCPScatterStyle::setBrus
    //customPlot->legend->setBrush(QBrush(QColor(255,255,255,230)));

   // Qt::NoBrush


    // set it up
    plotter->replot();
    // save as image
    //QString str = this->graphs->at(i).
   //std::cout << "DEBUG NAME2: " << temp.getFileName()<< std::endl;

    plotter->savePng(temp.getFileName());
        plotter->saveJpg("test.jpg");
       // plotter->s
    // close graph
    plotter->close();
}

bool Grapher::addGraph(Graph g)
{
    this->graphs->push_back(g);
    return true;
}







 *
 */




