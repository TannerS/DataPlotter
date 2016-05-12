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

    private:
        QCustomPlot* plotter;
        QVector<Graph>* graphs;
        QCPCurve* curve;
};

#endif // GRAPHER_H
