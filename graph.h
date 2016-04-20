#ifndef GRAPHS_H
#define GRAPHS_H
#include <QString>

class Graph
{
    public:
        Graph();
        void setFileName(QString);
        QString getFileName();
        void setXAxisVector(QVector<double>);
        void setYAxisVector(QVector<double>);
        QVector<double> getXAxisVector();
        QVector<double> getYAxisVector();
        void setMin(float);
        void setMax(float);
        float getMin();
        float getMax();

    private:
        QString file_name;// = QString::fromStdString(name);
        QVector<double> x;
        QVector<double> y;
        float min;
        float max;
};

#endif // GRAPHS_H
