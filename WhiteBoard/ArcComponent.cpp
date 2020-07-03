#include "DrawComponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
class ArcComponent : public DrawComponent{
private :
    int x;
    int y;
    int width;
    int height;
    int startAngle;
    int spanAngle;
    int minX=0;
    int minY=0;
    int maxX=0;
    int maxY=0;
    QVector<QPoint> *pointVector=nullptr;
    QString colorString;

public:
   ArcComponent(int x,int y ,int width,int height,int startAngle,int spanAngle,QString color){
    this->x=x;
       this->y = y;
       this->width = width;
       this->height =height;
       this->spanAngle=spanAngle*(16);
       this->startAngle=startAngle*(16);
       this->colorString = color;
   }
   QString toString() {
       return "Arc";
   }


   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointsVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
QPoint A(this->pointVector->at(0));
QPoint B(this->pointVector->at(size-1));
int Ax=A.rx();
int Ay=A.ry();
int width = Ax-B.rx();
int height = Ay-B.ry();
    painter->drawArc(Ax,Ay,width,height,120*16,180*16);
   }



void drawComponent(QPainter *painter){
QTextStream(stdout) << "Arc component"<<endl;

    if(x<0)x=0;
    if(y<0)y=0;
    if(width<0) width=0;
    if(height<0) height=0;
    if(pointVector!=nullptr){
        int size=this->pointVector->size();
 QTextStream(stdout) << "Line component..."<<QString::number(size)<<endl;
 QPoint A(this->pointVector->at(0));
 QPoint B(this->pointVector->at(size-1));
 int Ax=A.rx();
 int Ay=A.ry();
 int width = Ax-B.rx();
 int height = Ay-B.ry();
 if(Ax>B.rx()){
     minX=B.rx();
     maxX=Ax;
 }
 else{
     minX=Ax;
     maxX=B.rx();
 }
 if(Ay>B.ry()){
     minY=B.ry();
     maxY=Ay;
 }
 else{
     minY=Ay;
     maxY=B.ry();
 }
     painter->setPen(colorString);
     painter->drawArc(Ax,Ay,width,height,120*16,180*16);

        return;
    }
    QColor color(colorString);
    painter->setPen(color);
    painter->drawArc(x,y,width,height,startAngle,spanAngle);


}

bool canSelect(QPoint *currentPoint){
 return false;
}


void selectComponent(QPainter *painter){
return;
}


void moveComponentByDistance(int dx, int dy) {
    if(this->pointVector==nullptr)return;
       for(int i=0;i<this->pointVector->size();i++){
           QPoint A = this->pointVector->at(i);
           QPoint B (A.rx()-dx,A.ry()-dy);
           this->pointVector->insert(i,B);
       }
    QTextStream(stdout)<<"Updated";
    }


QPoint * getXRange() {
    return new QPoint(this->minX,this->maxX);
}
QPoint * getYRange() {
  return new QPoint(this->minY,this->maxY);
}


};
