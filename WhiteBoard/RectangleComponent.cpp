#include "drawcomponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
class RectangleComponent : public DrawComponent{
private :
    int x;
    int y;
    int width;
    int height;
    bool rounded;
    int minX=0;
    int maxX=0;
    int minY=0;
    int maxY=0;

    QVector<QPoint> *pointVector=nullptr;
    QString colorString;

public:
    RectangleComponent(QVector<QPoint> *pointVector, bool rounded,QString color){
        this->x=0;
        this->y=0;
        this->width=0;
        this->height=0;
        this->rounded=rounded;
        this->pointVector=pointVector;
        this->colorString=color;
    }
   RectangleComponent(int x,int y ,int width,int height,bool rounded,QString color){
    this->x=x;
       this->y = y;
       this->width = width;
       this->rounded = rounded;
       this->height =height;
       this->colorString = color;
       this->pointVector=nullptr;
   }
   QString toString() {
       return "Rectangle";
   }

   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
if(size<=0)return;
QPoint lastPoint(this->pointVector->at(0));
QPoint currentPoint(this->pointVector->at(size-1));
int Ax=lastPoint.rx();
int Ay=lastPoint.ry();
int Bx=currentPoint.rx();
int By=currentPoint.ry();
int width= Ax- Bx;
int height=Ay-By;
if(height<0)height=height*(-1);
if(width<0) width=width*(-1);
    painter->drawRect(Ax,Ay,width,height);

   }
void drawComponent(QPainter *painter){
QTextStream(stdout) << "component"<<colorString<<endl;

    if(x<0)x=0;
    if(y<0)y=0;
    if(width<0) width=10;
    if(height<0) height=10;
    QColor color(colorString);

    painter->setPen(color);
    if(this->pointVector!=nullptr){
       int size=this->pointVector->size();
       if(size<=0)return;
        QPoint lastPoint(this->pointVector->at(0));
        QPoint currentPoint(this->pointVector->at(size-1));
        //QTextStream(stdout)<<"L.P:"<<lastPoint.rx()<<","<<lastPoint.ry()<<endl;
        //QTextStream(stdout)<<"C.P."<<currentPoint.rx()<<","<<currentPoint.ry()<<endl;

        int Ax=lastPoint.rx();
        int Ay=lastPoint.ry();
        int Bx=currentPoint.rx();
        int By=currentPoint.ry();
        int width= Ax- Bx;
        int height=Ay-By;
        this->minX=Ax;
        this->maxX=Ax;
        this->maxY=Ay;
        this->minY=Ay;
        if(Ax<Bx)maxX=Bx;
        else minX=Bx;

        if(Ay<By)maxY=By;
        else minY=By;
        if(height<0)height=height*(-1);
        if(width<0) width=width*(-1);
        this->x=Ax;
        this->y=Ay;
        this->width=width;
        this->height=height;
        //QTextStream(stdout)<<this->x<<","<<this->y<<","<<this->width<<","<<this->height<<"*****************"<<endl;

        if(rounded){
            painter->drawRoundedRect(x,y,width,height,20,15);
        }else{
               painter->drawRect(Ax,Ay,width,height);
        }
       return;
    }

    if(rounded ){
        painter->drawRoundedRect(x,y,this->width,this->height,20,15);
    }
    else{
        painter->drawRect(x,y,this->width,this->height);
    }
    return;
}


bool canSelect(QPoint *currentPoint){
    int Gx=currentPoint->rx();
    int Gy = currentPoint->ry();
    int x1=this->x;
    int y1=this->y;
    int x2=this->width+x1;
    int y2 = this->height+y1;
QTextStream(stdout)<<QString::number(x1)<<","<<QString::number(y1)<<"::"<<QString::number(x2)<<","<<QString::number(y2)<<endl;
    if (Gx>=x1 && Gx<=x2 && Gy>=y1 && Gy<=y2)return true;
    return false;
}

void selectComponent(QPainter *painter){
    int x1=this->x;
    int y1=this->y;
    int x2=this->width+x1;
    int y2 = this->height+y1;
    //here we have four points x1,y1 x2,y1 x1,y2 x2,y2



    painter->setPen(Qt::blue);
    painter->setBrush(QBrush(Qt::darkBlue));
    painter->drawEllipse(x1-2,y1-2,5,5);
    painter->drawEllipse(x2-2,y1-2,5,5);
    painter->drawEllipse(x1-2,y2-2,5,5);
    painter->drawEllipse(x2-2,y2-2,5,5);
    painter->setBrush(QBrush(Qt::white));

}

void moveComponentByDistance(int dx, int dy) {
if(this->pointVector==nullptr)return;
if(this->pointVector->size()<=0) return;

       QPoint A = this->pointVector->at(0);
       //QTextStream(stdout)<<A.rx()<<","<<A.ry()<<"move "<<dx<<","<<dy<<endl;
       //QTextStream(stdout)<<this->x<<","<<this->y<<","<<this->width<<","<<this->height<<endl;
       this->x=A.rx()+dx;
       this->y=A.ry()+dy;
       QPoint B (A.rx()+dx,A.ry()+dy);
       this->pointVector->insert(0,B);
       this->pointVector->removeLast();
       int newW=this->width+this->x;
       int newH=this->height+this->y;
       this->pointVector->append(QPoint(newW,newH));
       //QTextStream(stdout)<<this->x<<","<<this->y<<","<<this->width<<","<<this->height<<endl;



//QTextStream(stdout)<<"Updated";
}


QPoint * getXRange() {
    return new QPoint(this->minX,this->maxX);
}
QPoint * getYRange() {
    return new QPoint(this->minY,this->maxY);
}

};   //class definition ends
