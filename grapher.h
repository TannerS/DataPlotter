#ifndef GRAPHER_H
#define GRAPHER_H
#include "qcustomplot.h"
#include <QVector>
#include "graph.h"

class Grapher
{
    public:
        Grapher();
        QVector<Graph>* getGraphs();
        bool addGraph(Graph);
        void generateGraph(int);
        ~Grapher();
        void graphReset();
       // std::string getTime();
        //void setTime();

    private:
        QCustomPlot* plotter;
        QVector<Graph>* graphs;
        QCPCurve* curve;
        QCPItemText* time_stamp;


};

#endif // GRAPHER_H
