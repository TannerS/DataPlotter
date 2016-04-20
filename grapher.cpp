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
    //QString str = QString::fromStdString(name);
    //this->plotter = new QCustomPlot(plotter);
    //this->plotter = plotter;

// Graph temp = this->graphs->at(i);
    Graph temp(this->graphs->at(i));
    // add graph
    plotter->addGraph();
    // set vector data
    QVector<double> x(temp.getXAxisVector());
    QVector<double> y(temp.getYAxisVector());
    // add data to graph


   // std::cout << "DEBUG POINTS: "<< std::endl;

    for(int i = 0 ;i < 100; i++)
    {
        std::cout <<x[i] << " " << y[i] << std::endl;
    }



    plotter->graph(0)->setData(x, y);
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



    plotter->xAxis->setRange(x_data_range_min, x_data_range_max);
    plotter->yAxis->setRange(y_data_range_min, y_data_range_max);
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






