#include "graph.h"

Graph::Graph()
{


}

void Graph::setFileName(QString name)
{
    this->file_name = name;
}

QString Graph::getFileName()
{
    return this->file_name;
}

void Graph::setXAxisVector(QVector<double> x)
{
    this->x = x;
}

void Graph::setYAxisVector(QVector<double> y)
{
    this->y = y;
}

QVector<double> Graph::getXAxisVector()
{
    return this->x;
}

QVector<double> Graph::getYAxisVector()
{
    return this->y;
}

void Graph::setXMin(float min)
{
    this->xmin = min;
}

void Graph::setXMax(float max)
{
    this->xmax = max;
}

void Graph::setYMin(float min)
{
    this->ymin = min;
}

void Graph::setYMax(float max)
{
    this->ymax = max;
}

float Graph::getXMin()
{
    return this->xmin;
}

float Graph::getXMax()
{
    return this->xmax;
}

float Graph::getYMin()
{
    return this->ymin;
}

float Graph::getYMax()
{
    return this->ymax;
}

QString Graph::getPath()
{
    return this->path;
}

void Graph::setPath(QString path)
{
    this->path = path;
}

