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


       // plotter->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));

       // plotter->graph(0)->setScatterStyle(QCPScatterStyle::ssDot );
       // plotter->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssTriangle, 5));

        /*
         * QCPBars *myBars = new QCPBars(customPlot->xAxis, customPlot->yAxis);
customPlot->addPlottable(myBars);
// now we can modify properties of myBars:
myBars->setName("Bars Series 1");
QVector<double> keyData;
QVector<double> valueData;
keyData << 1 << 2 << 3;
valueData << 2 << 4 << 8;
myBars->setData(keyData, valueData);
customPlot->rescaleAxes();
customPlot->replot();
         *
         */



        // add graph
        plotter->addGraph();


        //QCPCurve* curve = new QCPCurve(plotter->xAxis, plotter->yAxis);
        //plotter->addPlottable(curve);

//plotter->xAxis->grid()->setZeroLinePen(Qt::NoPen);

        // fixes a lot
        plotter->graph(0)->setLineStyle((QCPGraph::LineStyle)QCPGraph::lsNone);

plotter->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc , 3));

    // set vector data
   // QVector<double> x(temp.getXAxisVector());
  //  QVector<double> x = temp.getXAxisVector();
    //QVector<double> y = temp.getYAxisVector();
    // add data to graph


   // std::cout << "DEBUG POINTS: "<< std::endl;

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

    //plotter->graph(0)->rescaleAxes();


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

