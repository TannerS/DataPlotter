#ifndef GRAPHER_H
#define GRAPHER_H


#include "qcustomplot.h"
#include "graph.h"
#include <QVector>

class Grapher
{
    public:
        Grapher();
        QVector<Graph> getGraphs();
        bool addGraph(Graph);

    private:
        QCustomPlot* plotter;
        QVector<Graph>* graphs;
        void generateGraph(int);
};

#endif // GRAPHER_H
