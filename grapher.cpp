#include "grapher.h"

// set plotter to 0 aka null
//********************************************test nullptr
Grapher::Grapher() : plotter(0)
{
    plotter = new QCustomPlot;



    mPlot->savePng(qApp->applicationDirPath()+"/output.png", 500, 300);



}

Grapher::~Grapher()
{
    if (plotter)
      delete plotter;

}



