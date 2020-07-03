
#include "DrawComponent.h"
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <QTextStream>
#include <QMessageBox>
class LineComponent : public DrawComponent{
private :
    int Ax;
    int Ay;
    int Bx;
    int By;
    int typeOfLine;
    int minX=0;
    int maxX=0;
    int minY=0;
    int maxY=0;
    QVector<QPoint> *pointVector=nullptr;
    QString colorString;

public:
    LineComponent(QVector<QPoint> *pointVector,int type,QString color){
        this->Ax=0;
        this->Ay=0;
        this->Bx=0;
        this->By=0;
        this->pointVector=pointVector;
        this->typeOfLine=type;
        this->colorString="black";

    }
   LineComponent(int Ax,int Ay ,int Bx,int By,int type,QString color){
    this->Ax=Ax;
       this->Ay = Ay;
       this->Bx = Bx;
       this->By =By;
       this->typeOfLine=type;
       this->colorString = color;
   }

   QString toString() {
       return "Line";
   }

   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
       if(size<=0)return;
QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
    painter->drawLine(this->pointVector->at(0),this->pointVector->at(size-1));
   }

void drawComponent(QPainter *painter){
QTextStream(stdout) << "Line component"<<endl;

    if(Ax<0)Ax=0;
    if(Ay<0)Ay=0;
    if(Bx<0) Bx=0;
    if(By<0) By=0;

    if(this->pointVector!=nullptr){

        int size=this->pointVector->size();
        if(size<=0)return;
        QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
 QPoint A=(this->pointVector->at(0));
 QPoint B=(this->pointVector->at(size-1));
this->Ax=A.rx();
this->Ay=A.ry();
 this->Bx=B.rx();
 this->By=B.ry();
 this->minX=A.rx();
 this->maxX=A.rx();
 this->maxY=A.ry();
 this->minY=A.ry();
 if(A.rx()<B.rx())maxX=B.rx();
 else minX=B.rx();

 if(A.ry()<B.ry())maxY=B.ry();
 else minY=B.ry();
            painter->drawLine(this->pointVector->at(0),this->pointVector->at(size-1));
        return;
    }


    QColor color(colorString);
    painter->setPen(Qt::black);

   int size=this->pointVector->size();
    painter->drawLine(this->pointVector->at(0),this->pointVector->at(size-1));

}

bool canSelect( QPoint *currentPoint){
if(this->pointVector==nullptr) return false;
if(this->pointVector->size()<=0) return false;
int x3=currentPoint->rx();
int y3=currentPoint->ry();
//suppose we have a line of some equation we already know two points on the check.
//now we have to check if the currentPoint lies on the same line as that of the other two points
//therfore, instead of calculating the equation of line and then figuring out whether the given point lies on the line or not
//it's better to check the three points are collinear or not. but we do not have the kind of precision in terms of clicking the point.
//as the user will click the line on a point which may be 1 or 2 pixels ahead or below the given line.
//therefore, we need to find the equation of line
int b,result,size;
double m=0.0;

b=0;
size=0;
result=0;
size=this->pointVector->size();
QPoint A=this->pointVector->at(0);
QPoint B=this->pointVector->at(size-1);
int x1=A.rx();
int x2=B.rx();
int y1=A.ry();
int y2=B.ry();
QTextStream(stdout)<<x1<<","<<x2<<" y "<<y1<<","<<y2<<endl;
int k=x2-x1;
int j=y2-y1;
if(k>0 || k<0) {
    m=(double)j/(double)k;
}
else{
    QTextStream(stdout)<<"x2-x1 "<<k<<endl;
}
b=(m*x1*-1)+y1;
//now we have the value of both intercep and slope in m and b variables respectively.
//now we have to figure out whether a given point is on,below,or above the line
result=(-(m*x3))+y3;

QTextStream(stdout)<<QString::number(x3)<<","<<QString::number(y3)<<" m "<<QString::number(m)<<" b "<<QString::number(b);
QTextStream(stdout)<<" result "<<QString::number(result)<<endl;
int minX=x1;
int maxX=x1;
int minY=y1;
int maxY=y1;

if(y1<y2)maxY=y2;
else minY=y2;

if (x1<x2){
    maxX=x2;
}
else{
    minX=x2;
}
 if(y3<minY || y3>maxY){
        QTextStream(stdout)<<"out of range"<<endl;
 return false;
 }
if(x3<minX || x3>maxX){
    QTextStream(stdout)<<"out of range of this component"<<endl;
    return false;
}
if ((result == b) || (result>=(b-3)) || (result<=(b-3))){
    return true;
}


return false;
}
void selectComponent(QPainter *painter){
    if(this->pointVector==nullptr)return;
    if(this->pointVector->size()<=0) return;
    int size=this->pointVector->size();

           QPoint A = this->pointVector->at(0);
           QPoint B=this->pointVector->at(size-1);

           painter->setBrush(QBrush(Qt::darkBlue));
           painter->drawEllipse(this->Ax,this->Ay,5,5);
           painter->drawEllipse(this->Bx,this->Ay,5,5);
           painter->setBrush(Qt::white);




    return;
}

void moveComponentByDistance(int dx, int dy) {
if(this->pointVector==nullptr)return;
if(this->pointVector->size()<=0) return;
int i=this->pointVector->size();

       QPoint A = this->pointVector->at(0);
       //QTextStream(stdout)<<A.rx()<<","<<A.ry()<<"move "<<dx<<","<<dy<<endl;
       //QTextStream(stdout)<<this->x<<","<<this->y<<","<<this->width<<","<<this->height<<endl;
       this->Ax=A.rx()+dx;
       this->Ay=A.ry()+dy;
       QPoint B (A.rx()+dx,A.ry()+dy);
       this->pointVector->insert(0,B);

       int newW=this->Bx+dx;
       int newH=this->By+dy;
       this->pointVector->removeLast();
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

};
