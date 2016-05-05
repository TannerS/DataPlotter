#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>

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
    Graph temp(this->graphs->at(i));
    // add graph
    plotter->addGraph();
    // create curve since our data needs it to do what it needs to do and can
    // only do it while using a curve
    curve = new QCPCurve(plotter->xAxis, plotter->yAxis);
    // add curve lines to graph
    plotter->addPlottable(curve);
    curve->setLineStyle((QCPCurve::LineStyle)QCPCurve::lsLine);
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


