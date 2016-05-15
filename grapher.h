#ifndef GRAPHER_H
#define GRAPHER_H
#include "qcustomplot.h"
#include <QVector>
#include "graph.h"

class Grapher
{
    // check .cpp file for more info
    public:
        Grapher();
        QVector<Graph*> getGraphs();
        bool addGraph(Graph*);
        void generateGraph(int);
        ~Grapher();
        void graphReset();
        void deleteGraphs();

    private:
        QCustomPlot* plotter;
        QVector<Graph*> graphs;
        QCPCurve* curve;
        QCPItemText* time_stamp;


};

#endif // GRAPHER_H
