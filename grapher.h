#ifndef GRAPHER_H
#define GRAPHER_H


#include "qcustomplot.h"
#include <QVector>
#include "graph.h"
#include <QThread>

class Grapher : public QThread
{
    public:
        Grapher();
        void addGraphs(QVector<Graph> );
        void generateGraphs();
        ~Grapher();
        void graphReset();
        void stop();
        void run();

    private:
        QCustomPlot* plotter;
        QVector<Graph> graphs;
        QCPCurve* curve;
        //void generateGraph(int);
};

#endif // GRAPHER_H
