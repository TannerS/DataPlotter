#include "grapher.h"
#include "graph.h"
#include "qcustomplot.h"

// set plotter to 0 aka null
//********************************************test nullptr
Grapher::Grapher()// : plotter(0)
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
    /*
    // http://www.qcustomplot.com/index.php/support/forum/201


    srand(time(nullptr));

    QVector<double> x(1000), y(1000);

    QString str = QString::fromStdString(name);




    //this->plotter = new QCustomPlot(plotter);
    //this->plotter = plotter;

    plotter->addGraph();

    plotter->graph(0)->setData(x, y);

    plotter->xAxis->setLabel("x");

    plotter->yAxis->setLabel("y");

    plotter->xAxis->setRange(-1000, 1000);

    plotter->yAxis->setRange(-1000, 1000);

    plotter->replot();

    plotter->savePng(str);

    plotter->close();

}




void MainWindow::plot()
{
    PlottedGraph* temp;

    std::string str[5] = {"test1.png","test2.png","test3.png","test4.png","test5.png"};


    for(int i = 0; i < 5; i++)
    {
        temp = (this->graphs->at(i));
        temp->generateGraph(ui->plotter,str[i]);
    }
/*

    for (int i = 0 ; i < 5; i++)
    {
        // generate some data:
        QVector<double> x(101), y(101); // initialize with entries 0..100
        for (int i=0; i<101; ++i)
        {
          x[i] = i/55.0 - 1; // x goes from -1 to 1
          y[i] = x[i]*x[i]; // let's plot a quadratic function
        }

        //when do u us x  nd y
        // create graph and assign data to it:
        ui->plotter->addGraph();
        ui->plotter->graph(0)->setData(x, y);
        // give the axes some labels:
        ui->plotter->xAxis->setLabel("x");
        ui->plotter->yAxis->setLabel("y");
        // set axes ranges, so we see all data:
        ui->plotter->xAxis->setRange(-1, 1);
       ui->plotter->yAxis->setRange(0, 1);
      ui->plotter->replot();
       ui->plotter->savePng("test.png");
    }
*/


}

bool Grapher::addGraph(Graph g)
{
    this->graphs->push_back(g);
    return true;
}






