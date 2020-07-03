#include "drawcomponent.h"
#include <QPainter>
#include <QColor>
#include <QTextStream>
#include <QMessageBox>
class FreeHandComponent : public DrawComponent{
private :
    QVector<QPoint> *pointVector;
    QString colorString;
    int minX=0;
    int minY=0;
    int maxX=0;
    int maxY=0;

public:
   FreeHandComponent(QVector<QPoint> *pointVector,QString color="black"){
    this->pointVector=pointVector;
    this->colorString = color;
   }

   QString toString() {
       return "Free Hand";
   }

   void drawComponent(QPainter *painter,QVector <QPoint> *pointVector){
//       this->pointVector=pointVector;
       int size=this->pointVector->size();
QTextStream(stdout) << "Free hand component..."<<QString::number(size)<<endl;
int i=0;
       for(i=0;i<size-1;i++){
           if((i+1)>=this->pointVector->size()-1)break; //this is not needed bt just to be safe we have included this condition
           painter->setPen(QColor("black"));
           painter->drawLine(this->pointVector->at(i),this->pointVector->at(i+1));

   }


       QTextStream(stdout)<<"out of"<<endl;
   }

void drawComponent(QPainter *painter){
QTextStream(stdout) << "Free hand component"<<QString::number(pointVector->size())<<endl;
    painter->setPen(QColor(colorString));

int size=this->pointVector->size();
int i=0;
for( i=0;i<size-1;i++){
    if((i+1)>=(size-1))break; //this is not needed bt just to be safe we have included this condition
        painter->setPen(QColor("black"));
        painter->drawLine(this->pointVector->at(i),this->pointVector->at(i+1));
        QPoint A=this->pointVector->at(i);
        QPoint B=this->pointVector->at(i+1);
        this->minX=A.rx();
        this->maxX=A.rx();
        this->maxY=A.ry();
        this->minY=A.ry();
        if(A.rx()<B.rx())maxX=B.rx();
        else minX=B.rx();

        if(A.ry()<B.ry())maxY=B.ry();
        else minY=B.ry();

    }

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
