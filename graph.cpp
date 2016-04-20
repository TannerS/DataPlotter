#include "graph.h"

graph::graph()
{


}

void setFileName(QString name)
{
    this->file_name = name;
}

QString getFileName()
{
    return this->file_name;
}

void setXAxisVector(QVector<double> x)
{
    this->x = x;
}

void setYAxisVector(QVector<double> y)
{
    this->y = y;
}

QVector<double> getXAxisVector()
{
    return this->x;
}

QVector<double> getYAxisVector()
{
    return this->y;
}

void setMin(float min)
{
    this->min = min;
}

void setMax(float max)
{
    this->max = max;
}

float getMin()
{
    return this->min;
}

float getMax()
{
    return this->max;
}
