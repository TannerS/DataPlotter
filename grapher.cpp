#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>
#include "mainwindow.h"

// constructor
// allocate objects
Grapher::Grapher() : plotter(nullptr)
{
    plotter = new QCustomPlot;
    time_stamp = new QCPItemText(plotter);
    plotter->addItem(time_stamp);
}
// deallocate objects
Grapher::~Grapher()
{
    delete plotter;

    for(int i = 0; i < graphs.size(); i++)
    {
        if(graphs.at(i) != nullptr)
            delete graphs.at(i);
    }

    delete curve;
    delete time_stamp;
}
// return graphs
QVector<Graph*> Grapher::getGraphs()
{
    return this->graphs;
}
// generate graphs based on index of vector
void Grapher::generateGraph(int i)
{
    // create temp graph object
    Graph* temp(this->graphs.at(i));
    // add graph to UI
    plotter->addGraph();
    // create curve since our data needs it to do what it needs to do and can
    // only do it while using a curve
    curve = new QCPCurve(plotter->xAxis, plotter->yAxis);
    // add curve lines to graph
    plotter->addPlottable(curve);
    // set styles
    curve->setLineStyle((QCPCurve::LineStyle)QCPCurve::lsLine);
    curve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 1));
    // plot the data
    curve->setData(temp->getXAxisVector(), temp->getYAxisVector());
    // set axis label
    plotter->xAxis->setLabel("X");
    // sext axis label
    plotter->yAxis->setLabel("Y");
    // set graph size plus offset
    float x_data_range_min = temp->getXMin();
    float y_data_range_min = temp->getYMin();
    float x_data_range_max = temp->getXMax();
    float y_data_range_max = temp->getYMax();
    // set ranges with offset
    plotter->xAxis->setRange(x_data_range_min-5, x_data_range_max+5);
    // here we do a larger offset (-10) so we can fit the timestamp in graph
    plotter->yAxis->setRange(y_data_range_min-10, y_data_range_max+5);
    // deploy graph
    plotter->replot();
    // set time stamp style and settings
    time_stamp->setColor(QColor(0, 0, 255));
    time_stamp->setText(QString::fromStdString(temp->getTime()));
    time_stamp->setPositionAlignment(Qt::AlignBottom | Qt::AlignRight);
    time_stamp->setClipToAxisRect(true);
    time_stamp->position->setType(QCPItemPosition::ptAxisRectRatio);
    time_stamp->position->setCoords(1,1);
    // save as image in same dir
    plotter->savePng(temp->getFileName());
    // close graph
    plotter->close();
    // clear data for next graph
    // this fixed problem with graph
    // drawing over last set
    curve->clearData();
    // safetly precautions
    plotter->graph()->clearData();
}
// add graph object to vector
bool Grapher::addGraph(Graph* g)
{
    this->graphs.push_back(g);
    return true;
}
// reset graph, this fixed earlier
// issue with graphs overwrtting other graphs
// in multiple runs
// possible to not be needed anymore since
// moving to pointer objects in vector
// needs testing
void Grapher::graphReset()
{
    this->graphs.clear();
}
// delete graphs for any reason you need
void Grapher::deleteGraphs()
{
    for(int i = 0; i < graphs.size(); i++)
    {
        if(graphs.at(i) != nullptr)
            delete graphs.at(i);
    }
    // deleting wont change size
    // of vector, objects are there
    // but as null
    graphs.clear();
}

