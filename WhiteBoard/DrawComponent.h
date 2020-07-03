#ifndef DRAWCOMPONENT_H
#define DRAWCOMPONENT_H

#include <QPainter>
class DrawComponent
{
public:

    virtual void drawComponent(QPainter *pianter)=0;
    virtual void drawComponent(QPainter *painter,QVector<QPoint> *pointVector)=0;
    virtual QString toString()=0;
    virtual bool canSelect(QPoint *currentPoint)=0;
    virtual void selectComponent(QPainter *painter)=0;
    virtual void moveComponentByDistance(int dx,int dy)=0;
    virtual QPoint* getXRange()=0;
    virtual QPoint* getYRange()=0;
};

#endif // DRAWCOMPONENT_H
