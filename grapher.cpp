#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"
#include <iostream>
#include "mainwindow.h"

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
    plotter->yAxis->setRange(y_data_range_min-10, y_data_range_max+5);
    // set it up
    plotter->replot();





   // QCPAxisRect* bottom_axis = new QCPAxisRect(plotter);
   // bottom_axis->setupFullAxesBox(true);
   //bottom_axis->axes(QCPAxis::atBottom)->setRange(-45, 45);
    //(bottom_axis->axes(QCPAxis::atBottom)).set
  // plotter->plotLayout()->addElement(1,0, bottom_axis);

  //  plotter->addPlottable(bottom_axis);
   //
   // bottom_axis->

            QCPItemText* time_stamp = new QCPItemText(plotter);
    plotter->addItem(time_stamp);

    //time_stamp->position->setAxes(bottom_axis->axis(QCPAxis::atBottom), bottom_axis->axis(QCPAxis::atLeft));


    time_stamp->setColor(QColor(0, 0, 255));
    time_stamp->setText("TESTINGhhhhhhhhhhh");
   time_stamp->setPositionAlignment(Qt::AlignBottom | Qt::AlignRight);
    time_stamp->setClipToAxisRect(true);
   time_stamp->position->setType(QCPItemPosition::ptAxisRectRatio);
//  time_stamp->position->setCoords();
  time_stamp->position->setCoords(1,1);
   // time_stamp->setFont(QFont(Qt::fofont().family(), 16));
   // time_stamp->setPen(QPen(Qt::black));
   // time_stamp->setPadding(QMargins::setLeft(6));
//time_stamp->setPositionAlignment(plotter->axisRect()->bottom());
//time_stamp->setp




    // save as image
    plotter->savePng(temp.getFileName());
    // close graph
    plotter->close();
    // clear data for next graph (if need be)
    curve->clearData();

    plotter->graph()->clearData();

}

bool Grapher::addGraph(Graph g)
{
    this->graphs->push_back(g);
    return true;
}

void Grapher::graphReset()
{
    this->graphs->clear();
}


